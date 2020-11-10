/*
** EPITECH PROJECT, 2020
** nm
** File description:
** elf 64
*/

#include "nm.h"

static int verif_elf64_format(Elf64_Ehdr *elf64, char *filepath,
                            char *binary_name)
{
    if (elf64->e_ident[EI_MAG0] != ELFMAG0
    || elf64->e_ident[EI_MAG1] != ELFMAG1
    || elf64->e_ident[EI_MAG2] != ELFMAG2
    || elf64->e_ident[EI_MAG3] != ELFMAG3
    || (elf64->e_type != ET_EXEC
    && elf64->e_type != ET_REL
    && elf64->e_type != ET_DYN)) {
        fprintf(stderr, "%s: %s: File format not recognized\n",
                binary_name, filepath);
        return (-1);
    } else
        return (1);
}

static int print_sym64(Elf64_Sym *array_sym, long int size, Elf64_Shdr *shdr,
                        unsigned char *array)
{
    Elf64_Sym sym;
    char character_sym;

    for (int i = 0; i < size; i++) {
        sym = array_sym[i];
        if (sym.st_info != STT_FILE && sym.st_name != 0) {
            character_sym = get_type_sym_64elf(&sym, shdr);
            ((unsigned int)sym.st_value == 0 &&
            (character_sym == 'w' || character_sym == 'U')) ?
            printf("         %c %s\n",
            get_type_sym_64elf(&sym, shdr), &array[sym.st_name]) :
            printf("%08x %c %s\n", (unsigned int)sym.st_value,
            get_type_sym_64elf(&sym, shdr), &array[sym.st_name]);
        }
    }
    return (0);
}

static int print_flag_64(Elf64_Ehdr *elf64, Elf64_Shdr *shdr, void *data,
                        info_args_t info_args)
{
    Elf64_Sym *array_sym = NULL;
    unsigned char *array = NULL;
    long int save_size = 0;
    bool to_print = false;
    int nbr_arg = info_args.nbr_arg;
    char *filename = strdup(info_args.filename);

    for (int i = 0; i < elf64->e_shnum; i++)
        if (shdr[i].sh_type == SHT_SYMTAB) {
            array = data + shdr[shdr[i].sh_link].sh_offset;
            array_sym = (Elf64_Sym *)((char *)elf64 + shdr[i].sh_offset);
            save_size = shdr[i].sh_size / shdr[i].sh_entsize;
            i = elf64->e_shnum;
            to_print = true;
        }
    (to_print && nbr_arg > 2) ? printf("\n%s:\n", filename) : 0;
    free(filename);
    return ((to_print) ? print_sym64(array_sym, save_size, shdr, array) : -1);
}

int	my_nm64(void *data, long size, info_args_t info_args)
{
    Elf64_Ehdr *elf64 = (Elf64_Ehdr *)data;
    Elf64_Shdr *shdr = (Elf64_Shdr *)((char *)data + elf64->e_shoff);
    int ret = check_truncate_elf64(elf64, shdr, size);

    if (verif_elf64_format(elf64,
        info_args.filename, info_args.binary_name) == -1)
        return (84);
    else if (ret == -1 || ret == -2) {
        fprintf(stderr, "%s: %s: %s\n", info_args.binary_name,
        info_args.filename, (ret == -2) ?
            "File format not recognized" : "File truncated");
        return (84);
    }
    (print_flag_64(elf64, shdr, data, info_args) == -1) ?
    printf("%s: %s: %s\n", info_args.binary_name, info_args.filename,
    "no symbols") : 0;
    return (0);
}