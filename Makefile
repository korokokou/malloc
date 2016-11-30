# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 21:45:12 by takiapo           #+#    #+#              #
#    Updated: 2016/11/30 07:08:03 by takiapo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_malloc_$(HOSTTYPE).so

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

WFLAGS = -Wall -Wextra -Werror -g

CC = gcc 

LIBFLAG = -shared

SRCDIR = src/

OBJDIR = obj

LIB = -L libft/ -lft

SRC = 	\
		malloc.c \
		free.c
	#	src/show_alloc_mem.c

OBJECTS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))

INCLUDE = -I includes/


all : $(NAME)

$(NAME) : $(LIBFT) $(OBJECTS)
	make -C libft/
	$(CC) -o  $(NAME) $(OBJECTS) $(LIBFLAG) $(WFLAGS) $(INCLUDE) $(LIB) -g 
	ln -fs $(NAME) libft_malloc.so

$(LIBFT)  : libft/libft.a
	make -C libft/

$(OBJDIR)/%.o : $(addprefix $(SRCDIR), %.c)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@  -c $^ -g

clean :
	echo 'clean'
	make -C libft/ clean
	rm -rf $(OBJECTS)

fclean : clean
	echo 'fclean'
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all

