/*
** EPITECH PROJECT, 2020
** check sym
** File description:
** 64 elf
*/

#include "nm.h"

char check_definition64(Elf64_Sym *sym)
{
    switch (sym->st_shndx) {
        case SHN_UNDEF:
            if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
                return ('U');
            if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
                return ('u');
            if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
                return ('w');
            break;
        case SHN_COMMON:
            return ('C');
        default :
            return (0);
    }
    return (0);
}

char check_data64(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
    if ((shdr[sym->st_shndx].sh_type == SHT_PROGBITS
    && (shdr[sym->st_shndx].sh_flags & SHF_ALLOC))
    || (shdr[sym->st_shndx].sh_type == SHT_DYNAMIC))
        switch (ELF64_ST_BIND(sym->st_info)) {
        case STB_GLOBAL:
            return ((shdr[sym->st_shndx].sh_flags & SHF_WRITE) ? 'D' : 'R');
        case STB_LOCAL:
            return ((shdr[sym->st_shndx].sh_flags & SHF_WRITE) ? 'd' : 'r');
        case STB_WEAK:
            return ('W');
        default:
            return (0);
        }
    return (0);
}

static char ret_check(Elf64_Sym *sym, char def_char)
{
    switch (ELF64_ST_BIND(sym->st_info)) {
        case STB_GLOBAL:
            return ('T');
        case STB_LOCAL:
            return ('t');
        case STB_WEAK:
            return ('W');
        default:
            return (def_char);
    }
    return (0);
}

char check_exec64(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
    return ((ELF64_ST_TYPE(sym->st_info) == STT_FUNC
        && (shdr[sym->st_shndx].sh_flags & SHF_ALLOC)
        && shdr[sym->st_shndx].sh_type == SHT_PROGBITS
        && (shdr[sym->st_shndx].sh_flags & SHF_EXECINSTR)) ?
        ret_check(sym, 0) : 0);
}

char check_array64(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
    return (((ELF64_ST_TYPE(sym->st_info) == STT_OBJECT
        || ELF64_ST_TYPE(sym->st_info) == STT_NOTYPE)
        && (shdr[sym->st_shndx].sh_flags & SHF_WRITE)
        && (shdr[sym->st_shndx].sh_flags & SHF_ALLOC)) ?
        ret_check(sym, '?') : '?');
}