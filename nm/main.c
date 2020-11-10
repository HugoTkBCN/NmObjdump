/*
** EPITECH PROJECT, 2020
** nm
** File description:
** main
*/

#include "nm.h"

static void	my_nm(char *filename, char *binary_name, int nbr_arg)
{
    int fd;
    long size;
    void *data = init(filename, &fd, &size, binary_name);
    Elf64_Ehdr *elf;
    int ret = 0;
    info_args_t info_args;

    info_args.nbr_arg = nbr_arg;
    info_args.binary_name = strdup(binary_name);
    info_args.filename = strdup(filename);
    (data == NULL || data == MAP_FAILED) ? exit(84) : 0;
    elf = (Elf64_Ehdr*)data;
    ret = (elf->e_ident[EI_CLASS] == ELFCLASS32) ?
        my_nm32(data, size, info_args) :
        my_nm64(data, size, info_args);
    close(fd);
    free(info_args.binary_name);
    free(info_args.filename);
    (ret != 0) ? exit(84) : 0;
}

static void run_nm(int ac, char **av)
{
    if (strcmp(av[1], "-h") == 0)
        printf("Usage : %s [filename]\n", av[0]);
    else
        for (int i = 1; i < ac; i++)
            my_nm(av[i], av[0], ac);
}

int main(int ac, char **av)
{
    if (ac > 1)
        run_nm(ac, av);
    else {
        my_nm("./a.out",  av[0], ac);
        return (1);
    }
    return (0);
}
