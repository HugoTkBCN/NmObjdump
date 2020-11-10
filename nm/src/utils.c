/*
** EPITECH PROJECT, 2020
** nm
** File description:
** utils
*/

#include "nm.h"

void *print_error_ret_null(char *arg1, char *arg2, char *arg3)
{
    fprintf(stderr, "%s: '%s': %s\n", arg1, arg2, arg3);
    return (NULL);
}

void *init(char *filename, int *fd, long *size, char *binary_name)
{
    void *data;

    if (access(filename, R_OK) == -1)
        return (print_error_ret_null(binary_name, filename, "Permission denied"));
    else if ((*fd = open(filename, O_RDONLY, 0)) == -1)
        return (print_error_ret_null(binary_name, filename, "No such file"));
    *size = lseek((*fd), 0, SEEK_END);
    if (*size < 0) {
        fprintf(stderr, "error: lseek: %s\n", strerror(errno));
        return (NULL);
    } else if ((data = mmap(NULL, (*size), PROT_READ, MAP_SHARED,
            (*fd), 0)) == MAP_FAILED && (*size) > 0) {
        close((*fd));
        fprintf(stderr, "%s: Warning: '%s' is not an ordinary file\n",
            binary_name, filename);
        return (MAP_FAILED);
    }
    return (data);
}
