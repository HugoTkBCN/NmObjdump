/*
** EPITECH PROJECT, 2020
** nm 64 elf
** File description:
** sym
*/

#include "nm.h"

static char ret_type(Elf64_Sym *sym)
{
    switch (ELF64_ST_BIND(sym->st_info)) {
        case STB_GLOBAL:
            return ('B');
        case STB_LOCAL:
            return ('b');
        case STB_WEAK:
            return ('W');
        default:
            return (' ');
    }
    return (' ');
}

char get_type_sym_64elf(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
    char ret;

    if ((ret = check_definition64(sym)) != 0)
        return (ret);
    else if (sym->st_shndx == SHN_ABS)
        return ('A');
    ret = ret;
    if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT &&
        ELF64_ST_BIND(sym->st_info) == STB_WEAK)
        return ('V');
    else if (shdr[sym->st_shndx].sh_type == SHT_NOBITS) {
        ret = ret_type(sym);
        if (ret != ' ')
            return (ret);
    }
    return ((ret = check_exec64(sym, shdr)) != 0 ? ret :
        (ret = check_data64(sym, shdr)) != 0 ? ret : check_array64(sym, shdr));
}