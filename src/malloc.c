/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/01 13:12:37 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_malloc		g_wall = (t_malloc){0, 0, sizeof(t_map), sizeof(t_block)};

void			*block_it(void *ret, int size, t_map *map)
{
	t_block			data;

	data.size = size;
	data.next = NULL;
	data.freed = 1;
	(void )map;
	data.ptr = ret + g_wall.block_size;
	ft_bzero(ret, g_wall.block_size);
	ret = ft_memcpy(ret, (void *)(&data), g_wall.block_size);
	return (ret);
}

void			map_it(void *new, int type, int size)
{
	t_map			data;
	char			*cast;

	data.type = type;
	data.size = size;
	data.next = NULL;
	data.left = 0;
	data.region = NULL;
	cast = new;
	ft_bzero(new, g_wall.map_size);
	ft_memcpy(new, (void *)(&data), g_wall.map_size);
	((t_map *)new)->region = block_it(cast + g_wall.map_size, size, NULL);
}

void			*initialize(unsigned int type)
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
	char *tmp = new;
	int i = 0;
	while (i < zone_size)
	{
		tmp[i] = i;
			i++;
	}
	if (new == (void *)-1)
		return (NULL);
	map_it(new, type, zone_size);
	((t_map *)new)->end = &(tmp[i - 1]);
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

void			*downsize(t_block *current, int size, t_map *map)
{
	t_block			*temp;
	char			*cast;
	int				next_size;

	temp = current;
	cast = (char *)temp;
	temp->freed = 0;
	next_size = current->size - size - g_wall.block_size;
	temp->size = size - g_wall.block_size;
	temp->next = block_it(cast + size, next_size, map);
	return (temp->ptr);
}

void			*find_place(t_block *list, int size, t_map *map)
{
	t_block		*temp;

	temp = list;
	while (temp)
	{
		if (temp->freed && temp->size - size >= 0)
			return (downsize(temp, size, map));
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
		if (temp->type == type && temp->left < size)
		{
			if ((ret = find_place(temp->region, size, temp)) != NULL)
			{
				temp->left++;
				return ((char *)ret);
			}
		}
		temp = temp->next;
	}
	temp = initialize(type);
	ret = find_place(temp->region, size, temp);
	return ((char *)ret);
}

int				get_type_of_country(int size)
{
	if (size <= 128)
		return (0);
	else if (size <= 1024)
		return (1);
	else
		return (size);
}

void			*malloc(size_t size)
{
	int			type;
	void		*ret;

	if (g_wall.page_size == 0)
		g_wall.page_size = getpagesize();
	if (size <= 0 || g_wall.map_size == 0)
		return (NULL);
	type = get_type_of_country(size);
	size += g_wall.block_size;
	size = ALIGN(size);
	ret = find_zone(type, size);
	return (ret);
}
/*
void			*calloc(size_t count, size_t size)
{
	void		*ret;

	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}

void			*reallocf(void *ptr, size_t size)
{
	void		*ret;

	ret = realloc(ptr, size);
	if (ret != ptr)
		free(ptr);
	return (ret);
}

t_block			*get_list(void *ptr)
{
	t_block		*ret;
	char		*cast;

	cast = ptr;	
	cast -= g_wall.block_size;
	ret = (t_block *)cast;
	return (ret);
}

void			*upsize(t_block *current, size_t size)
{
	t_block		*next;

	next = current->next;
	current->size = size;
	current->next = block_it(current + size, next->size + current->size, NULL);
	current->next->next = next->next;
	return (current->ptr);
}

void			*realloc(void *ptr, size_t size)
{
	t_block		*current;
	t_block		*next;
		
	if (ptr == NULL)
		return (malloc(size));
	if (!check(ptr, NULL))
		return (NULL);
	if (size == 0)
	{
		free(ptr);
		return (find_zone(0, 0));
	}
	current = get_list(ptr);
	if ((size_t)current->size == size)
		return (ptr);
	else if ((size_t)current->size < size)
	{
		next = current->next;
		downsize(current, size, NULL);
		current->next->next = next->next;
		return (current->ptr);
	}
	else
		return (upsize(current, size));
}
*/
