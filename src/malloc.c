/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2016/11/24 16:33:36 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_malloc				g_wall = (t_malloc){0, 0, sizeof(t_map), sizeof(t_block)};

void					*block_it(void *ret, int size)
{
	t_block			data;

	data.size = size;
	data.next = NULL;
	data.freed = 0;
	data.ptr = ret;
	ret = memcpy(ret, (void *)(&data), g_wall.block_size);
	return (ret);
}

void					map_it(void *new, int size, int type)
{
	t_map				data;

	data.type = type;
	data.size = size;
	data.next = NULL;
	data.region = block_it(new + g_wall.map_size, size);
	memcpy(new, (void *)(&data), g_wall.map_size);
}

void					*initialize(unsigned int type)
{
	void				*new;
	t_map				*temp;
	int					zone_size;

	if (type == 0)
		zone_size = g_wall.page_size << 1;
	else if (type == 1)
		zone_size = g_wall.page_size << 3;	
	else
		zone_size = type;
	new = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
			-1, 0);
	if (new == (void *)-1)
		return (NULL);
	map_it(new, type, zone_size);
	if (!g_wall.countries)
		return (g_wall.countries = new); 
	else
	{
		temp = g_wall.countries;
		while (temp->next)
			temp = temp->next;
	}
	return (temp->next = new);
}

void					*downsize(t_block *current, int size)
{
	t_block			*temp;
	int				next_size;

	temp = current;
	temp = block_it(temp, size);
	temp->next = block_it(temp + size, next_size);
	return (current);
}

void					*find_place(t_block *list, int size)
{
	int				j;
	t_block			*temp;

	temp = list;
	while (temp)
	{
		if (temp->freed && temp->size - size >= 0)
			return (downsize(temp, size));
		temp = temp->next;
	}
	return (NULL);
}

void					*find_zone(int size, int type)
{
	t_map				*temp;
	t_block				*ret;

	temp = g_wall.countries;
	ret = NULL;
	while (temp)
	{
		if (temp->type == type && temp->left < size)
		{
			if ((ret = find_place(temp->region, size)) != NULL)
				return (ret);
		}
		temp = temp->next;
	}
	temp = initialize(type);
	ret = find_place(temp->region, size);
	return (ret);
}

int						get_type_of_country(int size)
{
	if (size <= 128)
		return (0);
	else if (size <= 1024)
		return (1);
	else 
		return (size);
}

void					*malloc(size_t size)
{
	int 	type;

	if (g_wall.page_size == 0)
		g_wall.page_size = getpagesize();
	if (size <= 0 || g_wall.map_size == 0)
		return (NULL);
	if (g_wall.map_size == 0)
		g_wall.map_size = sizeof(t_map);
	type = get_type_of_country(size);
	size += g_wall.map_size;
	size = ALIGN(size);
	return (&g_wall.map_size);
}

#include <stdio.h>

int main()
{
	printf("%d\n", g_wall.map_size);
	malloc(0);
	printf("%d\n", g_wall.block_size);
	malloc(0);
	printf("%lu %lu\n", sizeof(int), sizeof(void *));
}
