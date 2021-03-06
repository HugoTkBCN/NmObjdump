/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** elf 32
*/

#include "objdump.h"

static int verif_elf32_format(Elf32_Ehdr *elf32, char *filepath,
                            char *binary_name)
{
    if (elf32->e_ident[EI_MAG0] != ELFMAG0
    || elf32->e_ident[EI_MAG1] != ELFMAG1
    || elf32->e_ident[EI_MAG2] != ELFMAG2
    || elf32->e_ident[EI_MAG3] != ELFMAG3
    || (elf32->e_type != ET_EXEC
    && elf32->e_type != ET_REL
    && elf32->e_type != ET_DYN)) {
        fprintf(stderr, "%s: %s: File format not recognized\n",
                binary_name, filepath);
        return (-1);
    } else
        return (1);
}

static void print_section(char *array, Elf32_Ehdr *elf32,
                        Elf32_Shdr *shdr, int line)
{
    unsigned char *footer = (unsigned char *)
        ((char *)elf32 + shdr[line].sh_offset);
    int address = shdr[line].sh_addr;
    unsigned int save = 0;

    printf("Contents of section %s:\n", &array[shdr[line].sh_name]);
    for (unsigned int i = 0; i < shdr[line].sh_size;) {
        (i % 16 == 0) ? printf(" %0*x ",
        get_size_address((long int)
        (shdr[line].sh_addr + shdr[line].sh_size)), address) : 0;
        printf("%02x", footer[i++]);
        (i % 4 == 0 && i % 16 && i < shdr[line].sh_size) ? printf(" ") : 0;
        address += (i % 16 == 0) ? 16 : 0;
        save = (i % 16 == 0 || i >= shdr[line].sh_size) ?
            print_char_ascii(i, save, footer, (char *)footer) : save;
    }
}

static void run_print_section32(char *tab, Elf32_Ehdr *elf32, Elf32_Shdr *shdr)
{
    for (int line = 0; line < elf32->e_shnum; line++)
        check_section_elf32(shdr, line) ?
            print_section(tab, elf32, shdr, line) : 0;
}

int my_objdump32(void *data, char *filename, long size, char *binary_name)
{
    Elf32_Ehdr *elf32 = (Elf32_Ehdr *)data;
    Elf32_Shdr *shdr = (Elf32_Shdr *)((char *)data + elf32->e_shoff);
    char *array = (char *)((char *)data + shdr[elf32->e_shstrndx].sh_offset);
    int ret = check_truncate_elf32(elf32, shdr, size);

    if (verif_elf32_format(elf32, filename, binary_name) == -1)
        return (84);
    else if (ret == -1 || ret == -2) {
        fprintf(stderr, "%s: %s: %s\n", binary_name, filename, (ret == -2) ?
            "File format not recognized" : "File truncated");
        return (84);
    }
    printf("\n%s:%5cfile format elf32-i386\n", filename, ' ');
    printf("architecture: i386, flags 0x%.8x:\n", get_flag_32(elf32, shdr));
    print_flag_32(elf32, shdr);
    printf("start address 0x%08x\n\n", (unsigned int)elf32->e_entry);
    run_print_section32(array, elf32, shdr);
    return (0);
}
