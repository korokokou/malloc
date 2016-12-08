/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 14:12:43 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/08 19:06:21 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/mman.h>

# include "../libft/includes/libft.h"
# include "struct_malloc.h"

# define ABS(x)  ( ( (x) < 0) ? -(x) : (x) )
# define ALIGN(x) ((( ( ( x ) - 1 ) >> 4) << 4) + 16)
# define FLAG_PROT PROT_READ | PROT_WRITE
# define FLAG_MAP MAP_ANON | MAP_PRIVATE

void		free(void *p);
void		*malloc(size_t size);
void		*calloc(size_t , size_t);
int			check(t_block *p, t_map **country);
void		ft_print_memory(void *addr);
void show_alloc_mem(void);
#endif
