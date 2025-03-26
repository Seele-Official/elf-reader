#include "elf_64.h"
#include "elf_reader.cpp"
#include "log.h"
#include <ranges>
int main(){
    LOG.set_enable(true);

    elf64_reader elf_reader(file_reader("test.elf"));


    return 0;
}