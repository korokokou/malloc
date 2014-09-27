# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 21:45:12 by takiapo           #+#    #+#              #
#    Updated: 2014/09/27 16:25:19 by takiapo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_malloc_$(HOSTTYPE).so

WFLAGS = -Wall -Wextra -Werror

CC = gcc -o

LIBFLAG = -shared

SRCDIR = src

OBJDIR = obj

LIBFT = -L libft/ -lft

SRC = 	src/free.c\
		src/malloc.c\
		src/large_malloc.c\
		src/show_alloc_mem.c

OBJECTS = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDE = -I includes/

all : $(OBJECT) $(NAME)



$(NAME):
ifeq ($(HOSTTYPE),)
	@HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
	@make -C libft/
	@$(CC) $(NAME) $(LIBFLAG) $(WFLAGS) $(INCLUDE) $(LIBFT) $(SRC)

clean :
	@make -C libft/ clean
	@rm -rf $(OBJECTS)
	@echo 'clean'

fclean : clean
	@make -C libft/ fclean
	@rm -rf $(NAME)
	@echo 'fclean'

re: fclean all

