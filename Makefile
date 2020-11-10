##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## nm objdump
##

CC	=	gcc

NAME_NM	=	my_nm

NAME_OBJDUMP	=	my_objdump

SRC_NM	= 	./nm/main.c \
		./nm/src/my_nm32.c \
		./nm/src/my_nm64.c \
		./nm/src/my_nm32_utils.c \
		./nm/src/my_nm64_utils.c \
		./nm/src/my_nm32_sym.c \
		./nm/src/my_nm64_sym.c \
		./nm/src/utils.c \
		./nm/src/check_sym64.c \
		./nm/src/check_sym32.c

SRC_OBJDUMP	=	./objdump/main.c \
			./objdump/src/my_objdump32.c \
			./objdump/src/my_objdump64.c \
			./objdump/src/my_objdump32_utils.c \
			./objdump/src/my_objdump64_utils.c \
			./objdump/src/utils.c

OBJ_NM	=	$(SRC_NM:.c=.o)

OBJ_OBJDUMP	=	$(SRC_OBJDUMP:.c=.o)

CFLAGS	+= -I./include -I. -W -Wall -Werror -Wextra

all:	$(NAME_OBJDUMP) $(NAME_NM)

$(NAME_NM):	$(OBJ_NM)
	$(CC) -o $(NAME_NM) $(OBJ_NM)

$(NAME_OBJDUMP):	$(OBJ_OBJDUMP)
	$(CC) -o $(NAME_OBJDUMP) $(OBJ_OBJDUMP)

nm:	$(NAME_NM)

objdump:	$(NAME_OBJDUMP)

clean:
	@rm -rf $(OBJ_NM) $(OBJ_OBJDUMP)

fclean: clean
	@rm -rf $(NAME_NM) $(NAME_OBJDUMP)

re:	fclean all
