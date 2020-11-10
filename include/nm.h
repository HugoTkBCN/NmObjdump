/*
** EPITECH PROJECT, 2020
** nm
** File description:
** .h
*/

#ifndef _NM_H_
#define _NM_H_

#include <stdio.h>
#include <elf.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdbool.h>

typedef struct info_args_s {
    int nbr_arg;
    char *binary_name;
    char *filename;
} info_args_t;

void *init(char *, int *, long *, char *);
int my_nm32(void *, long, info_args_t);
int check_section_elf32(Elf32_Shdr *, int);
int check_truncate_elf32(Elf32_Ehdr *, Elf32_Shdr *, unsigned long);
int getSectionByName32(Elf32_Ehdr *, Elf64_Shdr *, char *, char *);
char get_type_sym_32elf(Elf32_Sym *, Elf32_Shdr *);
char check_definition32(Elf32_Sym *sym);
char check_data32(Elf32_Sym *sym, Elf32_Shdr *shdr);
char check_exec32(Elf32_Sym *sym, Elf32_Shdr *shdr);
char check_array32(Elf32_Sym *sym, Elf32_Shdr *shdr);
int my_nm64(void *, long, info_args_t);
int check_section_elf64(Elf64_Shdr *, int);
int check_truncate_elf64(Elf64_Ehdr *, Elf64_Shdr *, unsigned long);
int get_section64(Elf64_Ehdr *, Elf64_Shdr *, char *, char *);
char get_type_sym_64elf(Elf64_Sym *, Elf64_Shdr *);
char check_definition64(Elf64_Sym *);
char check_data64(Elf64_Sym *, Elf64_Shdr *);
char check_exec64(Elf64_Sym *, Elf64_Shdr *);
char check_array64(Elf64_Sym *, Elf64_Shdr *);

#endif /* _NM_H_ */
