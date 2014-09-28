/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 14:12:43 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/28 22:01:29 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include "struct_malloc.h"
# include <unistd.h>
# include <string.h>
# include <sys/mman.h>
# include "../libft/includes/libft.h"
# define ABS(x)  ( ( (x) < 0) ? -(x) : (x) )

void		*large_malloc(t_block **list, int *zone, t_block *temp);
void		*put_data(void *ret, int size, t_block *new, int state);
void		my_free(void *p);
void		initialise_first(t_malloc **wall);
#endif
