/*
** EPITECH PROJECT, 2020
** my_objdump
** File description:
** .h
*/

#ifndef OBJDUMP_H_
#define OBJDUMP_H_

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
#include "flags.h"

void *init(char *, int *, long *, char *);
int get_size_address(long int);
int my_objdump32(void *, char *, long, char *);
uint32_t get_flag_32(Elf32_Ehdr *, Elf32_Shdr *);
void print_flag_32(Elf32_Ehdr *, Elf32_Shdr *);
int check_section_elf32(Elf32_Shdr *, int);
int check_truncate_elf32(Elf32_Ehdr *, Elf32_Shdr *, unsigned long);
int my_objdump64(void *, char *, long, char *);
uint32_t get_flag_64(Elf64_Ehdr *, Elf64_Shdr *);
void print_flag_64(Elf64_Ehdr *, Elf64_Shdr *);
int check_section_elf64(Elf64_Shdr *, int);
int check_truncate_elf64(Elf64_Ehdr *, Elf64_Shdr *, long unsigned);
unsigned int print_char_ascii(unsigned int, unsigned int,
                            unsigned char *, char *);

#endif /* OBJDUMP_H_ */
