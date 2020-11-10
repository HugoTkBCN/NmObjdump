/*
** EPITECH PROJECT, 2020
** my_objdump
** File description:
** main
*/

#include "objdump.h"

void my_objdump(char *binary_name, char *filename)
{
    int fd;
    long size;
    void *data = init(filename, &fd, &size, binary_name);
    Elf64_Ehdr *elf;
    int ret = 0;

    (data == NULL || data == MAP_FAILED) ? exit(84) : 0;
    elf = (Elf64_Ehdr*)data;
    if (elf->e_ident[EI_CLASS] == ELFCLASS32)
        ret = my_objdump32(data, filename, size, binary_name);
    else
        ret = my_objdump64(data, filename, size, binary_name);
    close(fd);
    (ret != 0) ? exit(84) : 0;
}

int main(int ac, char **av)
{
    if (ac > 1) {
        if (strcmp(av[1], "-h") == 0)
            printf("Usage : %s [filename]\n", av[0]);
        else
            for (int i = 1; i < ac; i++)
                my_objdump(av[0], av[i]);
    } else {
        printf("Error: Run %s -h\n", av[0]);
        return (84);
    }
    return (0);
}
