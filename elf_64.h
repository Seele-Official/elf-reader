#pragma once
#include <cstdint>
#include <format>
#include <sys/types.h>
#include <unordered_map>
#include "bits.h"



namespace elf {
    
    constexpr uint32_t elf_magic =  htobed((uint32_t)0x7F454c46); // (0x7F 'E' 'L' 'F')
    class ident_class_t {
    private:
        uint8_t value;
    public:
        constexpr ident_class_t() : value(0) {}
        constexpr ident_class_t(uint8_t value) : value(value) {}

        inline ident_class_t& operator=(uint8_t value) {
            this->value = value;
            return *this;
        }

        inline operator uint8_t() const {
            return value;
        }

        
        
        static constexpr uint8_t elf32 = 1;
        static constexpr uint8_t elf64 = 2;

        inline std::string_view to_string() const {
            static std::unordered_map<uint8_t, std::string_view> name_map = {
                {elf32, "32-bit"},
                {elf64, "64-bit"}
            };
            
            auto it = name_map.find(value);
            return it == name_map.end() ? "UNKNOWN" : it->second;
        }

    };

    

    class ident_data_t {
    private:
        uint8_t value;
    public:
        constexpr ident_data_t() : value(0) {}
        constexpr ident_data_t(uint8_t value) : value(value) {}

        inline ident_data_t& operator=(uint8_t value) {
            this->value = value;
            return *this;
        }

        inline operator uint8_t() const {
            return value;
        }
        
        
        static constexpr uint8_t little_endian = 1;
        static constexpr uint8_t big_endian = 2;

        inline std::string_view to_string() const {
            static std::unordered_map<uint8_t, std::string_view> name_map = {
                {little_endian, "Little Endian"},
                {big_endian, "Big Endian"}
            };
            return name_map[value];
        }        

    };

    class ident_osabi_t {
    private:
        uint8_t value;
    public:
        constexpr ident_osabi_t() : value(0) {}
        constexpr ident_osabi_t(uint8_t value) : value(value) {}

        inline ident_osabi_t& operator=(uint8_t value) {
            this->value = value;
            return *this;
        }

        inline operator uint8_t() const {
            return value;
        }


        static constexpr uint8_t none = 0;
        static constexpr uint8_t hpux = 1;
        static constexpr uint8_t netbsd = 2;
        static constexpr uint8_t gnu = 3;
        static constexpr uint8_t linux_ = 4;
        static constexpr uint8_t solaris = 6;
        static constexpr uint8_t aix = 7;
        //

        inline std::string_view to_string() const {
            static std::unordered_map<uint8_t, std::string_view> name_map = {
                {none, "UNIX - System V"},
                {hpux, "HP-UX"},
                {netbsd, "NetBSD"},
                {gnu, "GNU"},
                {linux_, "Linux"},
                {solaris, "Solaris"},
                {aix, "AIX"}

            };
            auto it = name_map.find(value);
            return it == name_map.end() ? "UNKNOWN" : it->second;
        }


    };


    class type_t {
    private:
        uint16_t value;
    public:
        constexpr type_t() : value(0) {}
        constexpr type_t(uint16_t value) : value(value) {}

        inline type_t& operator=(uint16_t value) {
            this->value = value;
            return *this;
        }

        inline operator uint16_t() const {
            return value;
        }

        static constexpr uint16_t none = 0;
        static constexpr uint16_t relocatable = 1;
        static constexpr uint16_t executable = 2;
        static constexpr uint16_t shared = 3;
        static constexpr uint16_t core = 4;
        static constexpr uint16_t loos = 0xfe00;
        static constexpr uint16_t hios = 0xfeff;
        static constexpr uint16_t loproc = 0xff00;
        static constexpr uint16_t hiproc = 0xffff;

        inline std::string_view to_string() const {
            static std::unordered_map<uint16_t, std::string_view> name_map = {
                {none, "NONE"},
                {relocatable, "RELOCATABLE"},
                {executable, "EXECUTABLE"},
                {shared, "SHARED"},
                {core, "CORE"},
                {loos, "LOOS"},
                {hios, "HIOS"},
                {loproc, "LOPROC"},
                {hiproc, "HIPROC"}
            };

            auto it = name_map.find(value);
            return it == name_map.end() ? "UNKNOWN" : it->second;
        }
    };

    class machine_t {
    private:
        uint16_t value;
    public:
        constexpr machine_t() : value(0) {}
        constexpr machine_t(uint16_t value) : value(value) {}

        inline machine_t& operator=(uint16_t value) {
            this->value = value;
            return *this;
        }

        inline operator uint16_t() const {
            return value;
        }

        static constexpr uint16_t none = 0;
        static constexpr uint16_t m32 = 1;
        static constexpr uint16_t sparc = 2;
        static constexpr uint16_t i386 = 3;
        static constexpr uint16_t m68k = 4;

        inline std::string_view to_string() const {
            static std::unordered_map<uint16_t, std::string_view> name_map = {
                {none, "NONE"},
                {m32, "AT&T WE 32100"},
                {sparc, "SPARC"},
                {i386, "Intel 80386"},
                {m68k, "Motorola 68000"}
            };

            auto it = name_map.find(value);
            return it == name_map.end() ? "UNKNOWN" : it->second;
        }
    };

}

namespace elf64 {
    namespace sechdr {

        class type_t {
        private:
            uint32_t value;
        public:
            constexpr type_t() : value(0) {}
            constexpr type_t(uint32_t value) : value(value) {}

            inline type_t& operator=(uint32_t value) {
                this->value = value;
                return *this;
            }

            inline operator uint32_t() const {
                return value;
            }

            static constexpr uint32_t null = 0;
            static constexpr uint32_t progbits = 1;
            static constexpr uint32_t symtab = 2;
            static constexpr uint32_t strtab = 3;
            static constexpr uint32_t rela = 4;
            static constexpr uint32_t hash = 5;
            static constexpr uint32_t dynamic = 6;
            static constexpr uint32_t note = 7;
            static constexpr uint32_t nobits = 8;
            static constexpr uint32_t rel = 9;
            static constexpr uint32_t shlib = 10;
            static constexpr uint32_t dynsym = 11;
            static constexpr uint32_t init_array = 14;
            static constexpr uint32_t fini_array = 15;
            static constexpr uint32_t preinit_array = 16;
            static constexpr uint32_t group = 17;
            static constexpr uint32_t symtab_shndx = 18;
            static constexpr uint32_t num = 19;
            static constexpr uint32_t loos = 0x60000000;
            static constexpr uint32_t hios = 0x6fffffff;
            static constexpr uint32_t loproc = 0x70000000;
            static constexpr uint32_t hiproc = 0x7fffffff;
            static constexpr uint32_t louser = 0x80000000;
            static constexpr uint32_t hiuser = 0xffffffff;

            inline std::string_view to_string() const {
                static std::unordered_map<uint32_t, std::string_view> name_map = {
                    {null, "NULL"},
                    {progbits, "PROGBITS"},
                    {symtab, "SYMTAB"},
                    {strtab, "STRTAB"},
                    {rela, "RELA"},
                    {hash, "HASH"},
                    {dynamic, "DYNAMIC"},
                    {note, "NOTE"},
                    {nobits, "NOBITS"},
                    {rel, "REL"},
                    {shlib, "SHLIB"},
                    {dynsym, "DYNSYM"},
                    {init_array, "INIT_ARRAY"},
                    {fini_array, "FINI_ARRAY"},
                    {preinit_array, "PREINIT_ARRAY"},
                    {group, "GROUP"},
                    {symtab_shndx, "SYMTAB_SHNDX"},
                    {num, "NUM"},
                    {loos, "LOOS"},
                    {hios, "HIOS"},
                    {loproc, "LOPROC"},
                    {hiproc, "HIPROC"},
                    {louser, "LOUSER"},
                    {hiuser, "HIUSER"}
                };

                auto it = name_map.find(value);
                return it == name_map.end() ? "UNKNOWN" : it->second;
            }

        };

        class flags_t {
        private:
            uint64_t value;
        public:
            constexpr flags_t() : value(0) {}
            constexpr flags_t(uint64_t value) : value(value) {}
            
            inline flags_t& operator=(uint64_t value) {
                this->value = value;
                return *this;
            }

            inline operator uint64_t() const {
                return value;
            }

            static constexpr uint64_t write = 0x1;
            static constexpr uint64_t alloc = 0x2;
            static constexpr uint64_t execinstr = 0x4;
            static constexpr uint64_t merge = 0x10;
            static constexpr uint64_t strings = 0x20;
            static constexpr uint64_t info_link = 0x40;
            static constexpr uint64_t link_order = 0x80;
            static constexpr uint64_t os_nonconforming = 0x100;
            static constexpr uint64_t group = 0x200;
            static constexpr uint64_t tls = 0x400;
            static constexpr uint64_t compress = 0x800;
            static constexpr uint64_t maskos = 0x0ff00000;
            static constexpr uint64_t maskproc = 0xf0000000;

            inline std::string to_string() const {
                std::string res;
                if (value & write) res += "WRITE ";
                if (value & alloc) res += "ALLOC ";
                if (value & execinstr) res += "EXECINSTR ";
                if (value & merge) res += "MERGE ";
                if (value & strings) res += "STRINGS ";
                if (value & info_link) res += "INFO_LINK ";
                if (value & link_order) res += "LINK_ORDER ";
                if (value & os_nonconforming) res += "OS_NONCONFORMING ";
                if (value & group) res += "GROUP ";
                if (value & tls) res += "TLS ";
                if (value & compress) res += "COMPRESS ";
                if (value & maskos) res += "MASKOS ";
                if (value & maskproc) res += "MASKPROC ";
                if (res.empty()) return std::format("0x{:x}", value);
                res.pop_back();
                return res;
            }

        };


    }
    namespace symtab {
        class info_t {
        private:
            uint8_t value;
        public:
            constexpr info_t() : value(0) {}
            constexpr info_t(uint8_t value) : value(value) {}

            inline info_t& operator=(uint8_t value) {
                this->value = value;
                return *this;
            }

            inline operator uint8_t() const {
                return value;
            }

            static constexpr uint8_t b_local = 0;
            static constexpr uint8_t b_global = 1;
            static constexpr uint8_t b_weak = 2;
            static constexpr uint8_t b_loos = 10;
            static constexpr uint8_t b_hios = 12;
            static constexpr uint8_t b_loproc = 13;
            static constexpr uint8_t b_hiproc = 15;

            static constexpr uint8_t t_notype = 0;
            static constexpr uint8_t t_object = 1;
            static constexpr uint8_t t_func = 2;
            static constexpr uint8_t t_section = 3;
            static constexpr uint8_t t_file = 4;
            static constexpr uint8_t t_common = 5;
            static constexpr uint8_t t_tls = 6;
            static constexpr uint8_t t_loos = 10;
            static constexpr uint8_t t_hios = 12;
            static constexpr uint8_t t_loproc = 13;
            static constexpr uint8_t t_hiproc = 15;

            inline std::string to_string() const {
                static std::unordered_map<uint8_t, std::string_view> bind_name_map = {
                    {b_local, "LOCAL"},
                    {b_global, "GLOBAL"},
                    {b_weak, "WEAK"},
                    {b_loos, "LOOS"},
                    {b_hios, "HIOS"},
                    {b_loproc, "LOPROC"},
                    {b_hiproc, "HIPROC"}
                };

                static std::unordered_map<uint8_t, std::string_view> type_name_map = {
                    {t_notype, "NOTYPE"},
                    {t_object, "OBJECT"},
                    {t_func, "FUNC"},
                    {t_section, "SECTION"},
                    {t_file, "FILE"},
                    {t_common, "COMMON"},
                    {t_tls, "TLS"},
                    {t_loos, "LOOS"},
                    {t_hios, "HIOS"},
                    {t_loproc, "LOPROC"},
                    {t_hiproc, "HIPROC"}
                };
                auto bind_it = bind_name_map.find(value & 0xf);
                auto type_it = type_name_map.find(value >> 4);
                return std::format("{} {}", bind_it == bind_name_map.end() ? "UNKNOWN" : bind_it->second, type_it == type_name_map.end() ? "UNKNOWN" : type_it->second);
            }
        };
    }

    namespace reltab {
        class info_t {
        private:
            uint64_t value;
        public:
            constexpr info_t() : value(0) {}
            constexpr info_t(uint64_t value) : value(value) {}

            inline info_t& operator=(uint64_t value) {
                this->value = value;
                return *this;
            }

            inline operator uint64_t() const {
                return value;
            }

            uint32_t sym() const {
                return value >> 32;
            }
            uint32_t type() const {
                return value & 0xffffffff;
            }
        };
    }
}




struct elf_ident_t {
    // unsigned char e_ident[16]; 
    uint32_t             magic;      // magic number
    elf::ident_class_t   capacity;      // file class or capacity
    elf::ident_data_t    data;       // endianess
    uint8_t              version;    // elf header version number
    elf::ident_osabi_t   osabi;      // operating system abi
    uint8_t              abiversion; // abi version
    uint8_t              pad[7]; 
};


struct elf64_hdr_t {
    // unsigned char e_ident[16]; 
    elf_ident_t     ident;       // elf identification
    
    elf::type_t     e_type;      // object file type
    elf::machine_t  e_machine;   // machine architecture type
    uint32_t        e_version;   // object file version
    uint64_t        e_entry;     // the virtual address of the program entry point

    uint64_t        e_phoff;     // the program header table's file offset in bytes
    uint64_t        e_shoff;     // the section header table's file offset in bytes

    uint32_t        e_flags;     // processor-specific flags
    uint16_t        e_ehsize;    // the elf header's size in bytes

    uint16_t        e_phentsize; // the size in bytes of one entry in the program header table
    uint16_t        e_phnum;     // the number of entries in the program header table

    uint16_t        e_shentsize; // the size in bytes of one entry in the section header table
    uint16_t        e_shnum;     // the number of entries in the section header table

    uint16_t e_shstrndx;  // the section header table index of the entry associated with the section name string table
};


struct elf32_hdr_t : public elf_ident_t
{
    //TODO: implement
};

struct elf64_sechdr_t
{
    uint32_t                sh_name;       // the section name, an index into the section header string table
    elf64::sechdr::type_t   sh_type;       // the section type
    elf64::sechdr::flags_t  sh_flags;      // the section attributes
    uint64_t                sh_addr;       // the virtual address of the section in memory

    uint64_t                sh_offset;     // the byte offset of the section in the file
    uint64_t                sh_size;       // the section's size in bytes

    uint32_t                sh_link;       // the section header table index link
    uint32_t                sh_info;       // extra information

    uint64_t                sh_addralign;  // the section's alignment in memory and in the filek
    uint64_t                sh_entsize;    // the size in bytes of each entry in the section, if the section has fixed-size entries
};



struct elf64_sym_entry_t
{
    uint32_t                st_name;       // the symbol name, an index into the section header string table
    elf64::symtab::info_t   st_info;       // the symbol's type and binding attributes
    uint8_t                 st_other;      // reserved
    uint16_t                st_shndx;      // the section header table index of the section in which the symbol is defined
    uint64_t                st_value;      // the value of the symbol
    uint64_t                st_size;       // the size of the symbol
};

struct elf64_rela_entry_t
{
    uint64_t                r_offset;      // the location at which to apply the relocation action
    elf64::reltab::info_t   r_info;        // the symbol table index and the type of relocation
    int64_t                 r_addend;      // a constant addend used to compute the value to be stored into the relocatable field
};

struct elf64_rel_entry_t
{
    uint64_t                r_offset;      // the location at which to apply the relocation action
    elf64::reltab::info_t   r_info;        // the symbol table index and the type of relocation
};




struct elf64_proghdr_t
{

};

