/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 14:12:43 by takiapo           #+#    #+#             */
/*   Updated: 2016/11/24 12:02:30 by takiapo          ###   ########.fr       */
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
# define ALIGN(x) (( ( ( x - 1 ) >> 3) << 3) + 8)

void		*large_malloc(t_block **list, int *zone, t_block *temp);
void		*put_data(void *ret, int size, t_block *new, int state);
void		my_free(void *p);
void		initialise_first(t_malloc **wall);
#endif
