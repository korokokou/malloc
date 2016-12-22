/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:13:28 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 18:13:32 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_malloc g_wall;

void			*downsize(t_block *current, int size)
{
	t_block		*temp;
	t_block		*next;
	char		*cast;
	int			next_size;

	temp = current;
	cast = (char *)temp->ptr;
	next = temp->next;
	temp->freed = 0;
	next_size = temp->size - size;
	temp->size = size;
	temp->next = block_it(cast + size, next_size, next);
	if (temp->next == NULL)
	{
		if (next)
			temp->next = next;
		temp->size += next_size;
	}
	return (temp->ptr);
}

void			*block_it(void *ret, int size, t_block *next)
{
	t_block		*data;
	char		*cast;

	data = (t_block *)ret;
	if (size - g_wall.block_size < 0)
		return (NULL);
	data->size = size - g_wall.block_size;
	data->next = next;
	data->freed = 1;
	cast = ret;
	data->ptr = cast + g_wall.block_size;
	return (ret);
}

void			map_it(void *new, int type, int size)
{
	t_map		*data;
	char		*cast;

	if (type > 1)
		type = 3;
	data = (t_map *)new;
	data->type = type;
	data->size = size;
	data->next = NULL;
	data->left = 0;
	data->region = NULL;
	data->prev = NULL;
	cast = new;
	data->end = (t_map *)(cast + size);
	size -= g_wall.map_size;
	data->region = block_it(cast + g_wall.map_size, size, NULL);
}
