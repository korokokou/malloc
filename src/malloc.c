/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/07 20:43:21 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/malloc.h"

t_malloc		g_wall = (t_malloc){0, 0, sizeof(t_map), sizeof(t_block)};

void			*block_it(void *ret, int size, t_map *map)
{
	t_block		data;

	data.size = size - g_wall.block_size;
	if (data.size < 0)
		return (NULL);
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
	t_map		data;
	char		*cast;

	data.type = type;
	data.size = size;
	data.next = NULL;
	data.left = 0;
	data.region = NULL;
	data.prev = NULL;
	cast = new;
	size -= g_wall.map_size;
	ft_bzero(new, g_wall.map_size);
	ft_memcpy(new, (void *)(&data), g_wall.map_size);
	((t_map *)new)->region = block_it(cast + g_wall.map_size, size, NULL);
}

void			*initialize(unsigned int type)
{
	void		*new;
	t_map		*temp;
	int			zone_size;

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
	if (type > 1)
		type = 3;
	map_it(new, type, zone_size);
//	show_alloc_mem();
	if (!g_wall.countries)
		return (g_wall.countries = new);
	else
	{
		temp = g_wall.countries;
		while (temp->next)
			temp = temp->next;
		((t_map *)new)->prev = temp;
	}
	return (temp->next = new);
}

void			*downsize(t_block *current, int size, t_map *map)
{
	t_block		*temp;
	char		*cast;
	int			next_size;

	temp = current;
	cast = (char *)temp->ptr;
	ft_putstr("size : ");
	ft_putnbr(size);
	ft_putchar('\n');
	temp->freed = 0;
	next_size = current->size - size;
	ft_putchar('\n');
	temp->size = size;
	temp->next = block_it(cast + size, next_size, map);
	if (temp->next == NULL)
	{
		ft_putendl("hello");
		temp->size += next_size;
	}
//	show_alloc_mem();
	ft_putstr("  size : ");
	ft_putnbr(temp->size);
	ft_putchar('\n');
	ft_putstr("next size : ");
	ft_putnbr(next_size);
	ft_putchar('\n');
	return (temp->ptr);
}

void			*find_place(t_block *list, int size, t_map *map)
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
				return (downsize(temp, size, map));
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
	if (temp->type == type)// && temp->size =< size)
		{
			if ((ret = find_place(temp->region, size, temp)) != NULL)
			{
				temp->left++;
				temp->size -= size;
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
		return (size + g_wall.map_size);
}

void			*malloc(size_t size)
{
	int			type;
	void		*ret;

	ft_putendl("in");
	if (g_wall.page_size == 0)
		g_wall.page_size = getpagesize();
	if (size <= 0 || g_wall.map_size == 0)
		return (NULL);
	type = get_type_of_country(size);
	ft_putstr("entree ");
	ft_putnbr(size);
	ft_putchar('\n');
	size = ALIGN(size);
	ft_putstr("sortie ");
	ft_putnbr(size);
	ft_putchar('\n');
	ret = find_zone(type, size);
	if (((long)ret & 3))
	{
		ft_putstr("unalligned   ");
		ft_putnbr(size);
		ft_putstr("   -    ");
		ft_print_memory(ret);
		ft_putchar('\n');
	}
	ft_putendl("out");
	if (ret == NULL)
		ft_putendl("hum");
	return (ret);
}

void			*calloc(size_t count, size_t size)
{
	void		*ret;

	ft_putendl("in calloc");
	ret = malloc(count * size);
	size *= count;
	size = ALIGN(size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, size);
	show_alloc_mem();
	ft_putendl("out calloc");
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

	ft_putendl("in reaaloc");
	if (ptr == NULL)
		return (malloc(size));
	if (!check(ptr, NULL))
	{
		ft_putendl("out realloc");
		return (NULL);
	}
	if (size == 0)
	{
		free(ptr);
		ft_putendl("weird");
		return (find_zone(0, 0));
	}
	current = get_list(ptr);
	if ((size_t)current->size == size)
		{
			ft_putendl("out realloc");
			return (ptr);
		}
	else if ((size_t)current->size > size)
	{
		next = current->next;
		downsize(current, size, NULL);
		current->next->next = next->next;
			ft_putendl("out realloc");
		return (current->ptr);
	}
	else
	{
		ft_putendl("out realloc");
		return (upsize(current, size));
	}
}
