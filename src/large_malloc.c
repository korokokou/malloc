/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/27 13:03:45 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/malloc.h"
#include <stdio.h>
extern t_block		*g_large_malloc;
extern int			g_size;


void				*large_malloc(t_block **list, int zone, t_block *temp)
{
	t_block 		*data;

	data = *list;
	if (zone < 0)
		zone *= -1;
	temp = mmap(NULL, zone, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
			-1, 0);
	if (temp == (void *) -1)
		return (NULL);
	temp = put_data(temp, zone, temp, 2);
	if (!*list)
		*list = temp;
	else
	{
		while (data && data->next)
			data = data->next;
		data->next = temp;
		temp->back = data;
	}
	return (temp);
}
