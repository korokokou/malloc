/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 14:12:43 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 17:47:19 by takiapo          ###   ########.fr       */
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
# define ALIGN(x) ((( ( ( x ) - 1 ) >> 3) << 3) + 8)
# define FLAG_PROT PROT_READ | PROT_WRITE
# define FLAG_MAP MAP_ANON | MAP_PRIVATE
# define MAP_SIZE ALIGN(sizeof(t_map))
# define BLOCK_SIZE ALIGN(sizeof(t_block))

void		*malloc(size_t size);
void		*calloc(size_t , size_t);
void		*realloc(void *, size_t);
void		free(void *p);

t_block		*get_list(void *ptr);
void		show_alloc_mem(void);

void		*block_it(void *, int, t_block *);
void		map_it(void *, int, int);

char		*find_zone (int, int);
int			check(t_block *p, t_map **country);
void		*downsize(t_block *current, int size);

#endif
