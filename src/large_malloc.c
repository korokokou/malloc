/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/28 21:55:13 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
extern t_malloc		*wall;

void				initialise_first(t_malloc **wall)
{
	t_malloc 		*temp;

	temp = mmap(NULL, (sizeof(t_malloc)), PROT_READ | PROT_WRITE, MAP_ANON |
			MAP_PRIVATE, -1, 0);
	if (temp == (void*)-1)
		return ;
	temp->tiny = NULL;
	temp->small = NULL;
	temp->large = NULL;
	temp->g_size = (sizeof(t_block));
	*wall = temp;
}

void				*large_malloc(t_block **list, int *zone, t_block *temp)
{
	t_block			*data;

	data = *list;
	if (*zone < 0)
		*zone *= -1;
	temp = mmap(NULL, *zone, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
			-1, 0);
	if (temp == (void *)-1)
		return (NULL);
	temp = put_data(temp, *zone, temp, 2);
	if (!*list)
		*list = temp;
	else
	{
		while (data && data->next)
			data = data->next;
		data->next = temp;
		temp->back = data;
	}
	*zone *= -1;
	return (temp);
}
