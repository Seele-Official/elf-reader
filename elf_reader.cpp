
#include <cstddef>
#include <cstdint>
#include <expected>
#include <fstream>
#include <memory>
#include <mutex>
#include <optional>
#include <span>
#include <string_view>
#include <iostream>
#include <exception>
#include <vector>

#include "elf_64.h"
#include "reflect.h"
#include "log.h"



class elf_reader_exception : public std::exception{
public:
    enum class error_t{
        file_read_error = 1,
        invalid_ident_magic = 2,
        invalid_ident_class = 3,
        invalid_ident_data = 4,
        section_index_out_of_range = 5
    };
private:
    error_t error;
public:
    explicit elf_reader_exception(error_t error) : error(error){}

    std::string_view name() const noexcept {
        switch (error){
            case error_t::file_read_error:
                return "file_read_error";
            case error_t::invalid_ident_magic:
                return "invalid_ident_magic";
            case error_t::invalid_ident_class:
                return "invalid_ident_class";
            case error_t::invalid_ident_data:
                return "invalid_ident_data";
            case error_t::section_index_out_of_range:
                return "section_index_out_of_range";
        }
    }

    const char* what() const noexcept override{
        return name().data();
    }


};

class file_reader{
private:
    std::ifstream file;
    std::mutex file_mutex;

    void* read(size_t offset, size_t size){
        std::lock_guard lock(file_mutex);
        auto res = new char[size];
        file.seekg(offset);
        file.read(res, size);
        if (file.fail()){
            return nullptr;
        }
        return res;
    }
public:
    explicit file_reader(std::string_view path){
        file.open(path.data(), std::ios::binary);
    }

    file_reader(const file_reader&) = delete;
    inline file_reader(file_reader&& other) : file(std::move(other.file)){}



    file_reader& operator=(const file_reader&) = delete;
    inline file_reader& operator=(file_reader&& other){
        file = std::move(other.file);
        return *this;
    }


    ~file_reader(){
        if (file.is_open()){
            file.close();
        }
    }

    template<typename return_t>
    std::unique_ptr<return_t> read_as_unique_ptr(size_t offset, size_t size = sizeof(return_t)){
        return std::unique_ptr<return_t>(static_cast<return_t*>(read(offset, size)));
    }

    template<typename return_t>
    std::vector<return_t> read_as_vector(size_t offset, size_t count){
        std::lock_guard lock(file_mutex);
        std::vector<return_t> res(count);
        file.seekg(offset);
        file.read(reinterpret_cast<char*>(res.data()), count * sizeof(return_t));
        if (file.fail()){
            return {};
        }
        return res;
    }

    std::vector<uint8_t> read_entire_file(){
        std::lock_guard lock(file_mutex);
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0);
        std::vector<uint8_t> res(size);
        file.read(reinterpret_cast<char*>(res.data()), size);
        if (file.fail()){
            return {};
        }
        return res;
    }

};

class elf64_section_t{
public:
    elf64_sechdr_t header;
private:
    std::vector<uint8_t> data;
public:
    elf64_section_t(elf64_sechdr_t header, std::vector<uint8_t>&& data) : header(header), data(std::move(data)){}

    template<typename T>
    inline std::span<T> view_table_as() const {
        return {(T*)(data.data()), data.size() / sizeof(T)};
    }

    inline std::string_view view_string(size_t offset) const {
        return {reinterpret_cast<const char*>(data.data() + offset)};
    }
};



class elf64_reader{
private:
    file_reader reader;
    std::unique_ptr<elf64_hdr_t> header;
    std::vector<elf64_sechdr_t> section_headers;



    std::vector<std::optional<elf64_section_t>> sections_cache;

public:
    template<typename T>
    static void to_hosted(elf::ident_data_t endianess, T& value){
        if (endianess == elf::ident_data_t::little_endian){
            forech_member(value, [](auto member){
                if constexpr (requires {ledtoh(*member);}) {
                    *member = ledtoh(*member);
                } else {
                    LOG.log("Unsupported convert type : \"{}\"\n", TYPE_NAME(*member));
                }
            });
        } else if (endianess == elf::ident_data_t::big_endian){
            forech_member(value, [](auto member){
                if constexpr (requires {ledtoh(*member);}){
                    *member = bedtoh(*member);
                } else {
                    LOG.log("Unsupported convert type : \"{}\"\n", TYPE_NAME(*member));
                }
            });
        }
    }

    static std::unique_ptr<elf64_hdr_t> read_header(file_reader& reader){
        std::unique_ptr<elf64_hdr_t> header = reader.read_as_unique_ptr<elf64_hdr_t>(0);
        if (!header){
            throw elf_reader_exception(elf_reader_exception::error_t::file_read_error);
        }

        if (header->ident.magic != elf::elf_magic){
            throw elf_reader_exception(elf_reader_exception::error_t::invalid_ident_magic);
        }

        if (header->ident.capacity != elf::ident_class_t::elf64){
            throw elf_reader_exception(elf_reader_exception::error_t::invalid_ident_class);
        }
        if (header->ident.data != elf::ident_data_t::little_endian && header->ident.data != elf::ident_data_t::big_endian){
            throw elf_reader_exception(elf_reader_exception::error_t::invalid_ident_data);
        }   

        to_hosted(header->ident.data, *header);
        return header;
    }

    static std::vector<elf64_sechdr_t> read_section_headers(file_reader& reader, elf64_hdr_t& header){
        std::vector<elf64_sechdr_t> section_headers = reader.read_as_vector<elf64_sechdr_t>(header.e_shoff, header.e_shnum);
        if (section_headers.empty()){
            throw elf_reader_exception(elf_reader_exception::error_t::file_read_error);
        }

        for (auto& hdr: section_headers){
            to_hosted(header.ident.data, hdr);
        }
        return section_headers;
    }

    elf64_reader(file_reader reader) : reader(std::move(reader)){
        header = read_header(this->reader);
        section_headers = read_section_headers(this->reader, *header);
        sections_cache.resize(section_headers.size());
        this->read_section(header->e_shstrndx);
    }

    const elf64_section_t& read_section(size_t index){
        if (index >= section_headers.size()){
            throw elf_reader_exception(elf_reader_exception::error_t::section_index_out_of_range);
        }

        if (sections_cache[index]){
            return *sections_cache[index];
        }

        auto& section_header = section_headers[index];
        auto data = reader.read_as_vector<uint8_t>(section_header.sh_offset, section_header.sh_size);
        if (data.empty()){
            throw elf_reader_exception(elf_reader_exception::error_t::file_read_error);
        }

        switch (section_header.sh_type){
            case elf64::sechdr::type_t::symtab:
            case elf64::sechdr::type_t::dynsym:
                for (size_t i = 0; i < data.size(); i += sizeof(elf64_sym_entry_t)){
                    elf64_sym_entry_t* sym = reinterpret_cast<elf64_sym_entry_t*>(data.data() + i);
                    to_hosted(this->header->ident.data, *sym);
                }
                break;
            case elf64::sechdr::type_t::rela:
                for (size_t i = 0; i < data.size(); i += sizeof(elf64_rela_entry_t)){
                    elf64_rela_entry_t* rela = reinterpret_cast<elf64_rela_entry_t*>(data.data() + i);
                    to_hosted(this->header->ident.data, *rela);
                }
                break;
            case elf64::sechdr::type_t::rel:
                for (size_t i = 0; i < data.size(); i += sizeof(elf64_rel_entry_t)){
                    elf64_rel_entry_t* rel = reinterpret_cast<elf64_rel_entry_t*>(data.data() + i);
                    to_hosted(this->header->ident.data, *rel);
                }
                break;
            
        
        }

        // TODO: Implement section type specific endianness conversion



        sections_cache[index] = elf64_section_t(section_header, std::move(data));
        return *sections_cache[index];
    }

    inline std::string_view get_section_name(size_t index){
        return sections_cache[header->e_shstrndx]->view_string(section_headers[index].sh_name);
    }


    inline const elf64_hdr_t& get_header(){
        return *header;
    }



    inline const std::vector<elf64_sechdr_t>& get_section_headers(){
        return section_headers;
    }

};