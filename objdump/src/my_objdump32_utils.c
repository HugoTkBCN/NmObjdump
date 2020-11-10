/*
** EPITECH PROJECT, 2020
** objdump elf32
** File description:
** utils
*/

#include "objdump.h"

uint32_t get_flag_32(Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
    uint32_t ret = 0;

    ret |= (elf->e_type == ET_REL) ? HAS_RELOC : ret;
    ret |= (elf->e_type == ET_EXEC) ? EXEC_P : ret;
    for (int i = 0; i < elf->e_shnum; i++)
        if (shdr[i].sh_type != SHT_SYMTAB || shdr[i].sh_type != SHT_DYNAMIC)
            ret |= HAS_SYMS;
    ret |= (elf->e_type == ET_DYN) ? DYNAMIC : ret;
    ret |= (elf->e_phnum != 0) ? D_PAGED : ret;
    return (ret);
}

void print_flag_32(Elf32_Ehdr *elf, Elf32_Shdr *shdr)
{
    int disp = 0;
    int to_disp = 0;

    disp = (elf->e_type == ET_REL) ? printf("HAS_RELOC") : disp;
    disp = (elf->e_type == ET_EXEC) ?
            printf((disp)? ", EXEC_P": "EXEC_P") : disp;
    for (int i = 0; i < elf->e_shnum; i++)
        if (shdr[i].sh_type != SHT_SYMTAB || shdr[i].sh_type != SHT_DYNAMIC)
            to_disp = 1;
    disp = (to_disp) ? printf((disp) ?
        ", HAS_SYMS": "HAS_SYMS") : disp;
    disp = (elf->e_type == ET_DYN) ?
        printf((disp) ? ", DYNAMIC": "DYNAMIC") : disp;
    (elf->e_phnum != 0) ? printf((disp) ? ", D_PAGED": "D_PAGED") : 0;
    printf("\n");
}

int	check_section_elf32(Elf32_Shdr *shdr, int i)
{
    bool ret = shdr[i].sh_type != SHT_NOBITS
            && shdr[i].sh_name
            && shdr[i].sh_size > 0
            && shdr->sh_flags != SHF_INFO_LINK
            && (shdr[i].sh_addr || (!shdr[i].sh_addr
            && shdr[i].sh_type != SHT_STRTAB
            && shdr[i].sh_type != SHT_RELA
            && shdr[i].sh_type != SHT_REL
            && shdr[i].sh_type != SHT_SYMTAB));

    return (ret);
}

int check_truncate_elf32(Elf32_Ehdr *elf, Elf32_Shdr *shdr, unsigned long size)
{
    if ((elf->e_shnum * elf->e_shentsize + elf->e_shoff) > size)
        return (-1);
    for (int i = 0; i < elf->e_shnum; i++)
        if (check_section_elf32(shdr, i)
            && (shdr[i].sh_size + shdr[i].sh_offset) > size)
            return (-2);
    return (0);
}
