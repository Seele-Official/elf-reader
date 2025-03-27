#include "elf_64.h"
#include "elf_reader.cpp"
#include "log.h"
#include <ranges>
int main(){
    LOG.set_enable(true);

    elf64_reader elf_reader(file_reader("test.elf"));


    // for (auto&& [i, section]: std::views::enumerate(elf_reader.get_section_headers())){
    //     LOG.log("Section {}:\n", i);
    //     LOG.log("    Name: {}\n", elf_reader.get_section_name(i));
    //     LOG.log("    Type: {}\n", section.sh_type.to_string());
    //     LOG.log("    Flags: {}\n", section.sh_flags.to_string());
    //     LOG.log("    Address: 0x{:x}\n", section.sh_addr);
    //     LOG.log("    Offset: 0x{:x}\n", section.sh_offset);
    //     LOG.log("    Size: 0x{:x}\n", section.sh_size);
    //     LOG.log("    Link: {}\n", section.sh_link);
    //     LOG.log("    Info: {}\n", section.sh_info);
    //     LOG.log("    Addralign: {}\n", section.sh_addralign);
    //     LOG.log("    Entsize: {}\n", section.sh_entsize);
    // }

    for (auto& sym: elf_reader.read_section(40).view_table_as<elf64_sym_entry_t>()){
        LOG.log("Symbol:\n");
        LOG.log("    Name: {}\n", elf_reader.read_section(41).view_string(sym.st_name));
        LOG.log("    Info: {}\n", sym.st_info.to_string());
        LOG.log("    Other: {}\n", sym.st_other);
        LOG.log("    Shndx: {}\n", sym.st_shndx);
        LOG.log("    Value: 0x{:x}\n", sym.st_value);
        LOG.log("    Size: 0x{:x}\n", sym.st_size);
    }

    return 0;
}