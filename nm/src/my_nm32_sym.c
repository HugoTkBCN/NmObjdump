/*
** EPITECH PROJECT, 2020
** nm 32 elf
** File description:
** sym
*/

#include "nm.h"

static char ret_type(Elf32_Sym *sym)
{
    switch (ELF32_ST_BIND(sym->st_info)) {
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

char get_type_sym_32elf(Elf32_Sym *sym, Elf32_Shdr *shdr)
{
    char ret;

    if ((ret = check_definition32(sym)) != 0)
        return (ret);
    else if (sym->st_shndx == SHN_ABS)
        return ('A');
    ret = ret;
    if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT &&
        ELF32_ST_BIND(sym->st_info) == STB_WEAK)
        return ('V');
    else if (shdr[sym->st_shndx].sh_type == SHT_NOBITS) {
        ret = ret_type(sym);
        if (ret != ' ')
            return (ret);
    }
    return ((ret = check_exec32(sym, shdr)) != 0 ? ret :
        (ret = check_data32(sym, shdr)) != 0 ? ret : check_array32(sym, shdr));
}