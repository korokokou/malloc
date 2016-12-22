/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 17:46:00 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc		g_wall = (t_malloc){0, 0, MAP_SIZE, BLOCK_SIZE};
pthread_mutex_t	g_malloc_lock;


void			*initialize(unsigned int type)
{
	void		*new;
	t_map		*temp;
	int			zone_size;

	if (type == 0)
		zone_size = g_wall.page_size * 50;
	else if (type == 1)
		zone_size = g_wall.page_size * 50 * 80;
	else
		zone_size = type;
	new = mmap(NULL, zone_size, FLAG_PROT, FLAG_MAP, -1, 0);
	if (new == (void *)-1)
		return (NULL);	
	map_it(new, type, zone_size);
	if (!g_wall.countries)
		return (g_wall.countries = new);
	temp = g_wall.countries;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	temp->next->prev = temp;
	return (new);
}

void			*find_place(t_block *list, int size)
{
	t_block		*temp;

	temp = list;
	while (temp)
	{
		if (temp->freed)
		{
			if (temp->size - size == 0)
			{
				temp->freed = 0;
				return (temp->ptr);
			}
			else if (temp->size - size > 0)
				return (downsize(temp, size));
		}
		temp = temp->next;
	}
	return (NULL);
}

char			*find_zone(int type, int size)
{
	t_map		*temp;
	t_block		*ret;

	temp = g_wall.countries;
	ret = NULL;
	while (temp)
	{
		if (temp->type == type)
		{
			if ((ret = find_place(temp->region, size)) != NULL)
			{
				temp->size -= size + g_wall.block_size;
				return ((char *)ret);
			}
		}
		temp = temp->next;
	}
	temp = initialize(type);
	ret = find_place(temp->region, size);
	return ((char *)ret);
}

int				get_type_of_country(int size)
{
	if (size <= 2048)
		return (0);
	else if (size <= 2048 * 20)
		return (1);
	else
		return (size + MAP_SIZE + BLOCK_SIZE);
}

void			*malloc(size_t size)
{
	int			type;
	void		*ret;

	if (g_wall.page_size == 0)
		g_wall.page_size = getpagesize();
	if (size <= 0 || g_wall.map_size == 0)
		return (NULL);
	pthread_mutex_lock(&g_malloc_lock);	
	size = ALIGN(size);
	type = get_type_of_country(size);
	ret = find_zone(type, size);
	pthread_mutex_unlock(&g_malloc_lock);	
	return (ret);
}
