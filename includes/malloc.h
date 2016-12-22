/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 14:12:43 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 18:32:00 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <pthread.h>
# include "../libft/includes/libft.h"
# include "struct_malloc.h"

# define ABS(x)  ( ( (x) < 0) ? -(x) : (x) )
# define ALIGN(x) ((( ( ( x ) - 1 ) >> 4) << 4) + 16)
# define FLAG_PROT PROT_READ | PROT_WRITE
# define FLAG_MAP MAP_ANON | MAP_PRIVATE
# define MAP_SIZE ALIGN(sizeof(t_map))
# define BLOCK_SIZE ALIGN(sizeof(t_block))

void		*malloc(size_t size);
void		*calloc(size_t count, size_t size);
void		*realloc(void *p, size_t size);
void		free(void *p);

t_block		*get_list(void *ptr);
void		show_alloc_mem(void);

void		*block_it(void *p, int size, t_block *next);
void		map_it(void *ret, int type, int size);

char		*find_zone (int type, int size);
int			check(t_block *p, t_map **country);
void		*downsize(t_block *current, int size);

#endif
