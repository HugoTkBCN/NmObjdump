/*
** EPITECH PROJECT, 2020
** nm 64 elf
** File description:
** utils
*/

#include "nm.h"

int get_section64(Elf64_Ehdr *elf, Elf64_Shdr *shdr, char *section,
                    char *strtab)
{
    int ret = -1;

    for (int i = 0; i < elf->e_shnum; i++)
        ret = !strcmp(&strtab[shdr[i].sh_name], section) ? i : ret;
    return (ret);
}

int check_section_elf64(Elf64_Shdr *shdr, int i)
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

int	check_truncate_elf64(Elf64_Ehdr *elf, Elf64_Shdr *shdr,
                        unsigned long size)
{
    if ((elf->e_shnum * elf->e_shentsize + elf->e_shoff) > size)
        return (-1);
    for (int i = 0; i < elf->e_shnum; i++)
        if (check_section_elf64(shdr, i)
            && (shdr[i].sh_size + shdr[i].sh_offset) > size)
            return (-2);
    return (0);
}
