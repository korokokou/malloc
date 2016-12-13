/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/13 09:33:38 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/malloc.h"

t_malloc		g_wall = (t_malloc){0, 0, sizeof(t_map), sizeof(t_block)};

void			*block_it(void *ret, int size, t_block *next)
{
	t_block		data;
	char		*cast;

	data.size = size - g_wall.block_size;
	if (data.size < 0)
		return (NULL);
	data.next = next;
	data.freed = 1;
	cast = ret;
	data.ptr = cast + g_wall.block_size;
	/* Debug */
	t_map *temp = NULL;
	if (!check(ret, &temp)){
		ft_putendl("seem we found something");
		ft_print_memory(ret);
		ft_putchar('\n');
	}
	else
	{
		temp = g_wall.countries;
			ft_putendl("in");
		while (temp)
		{	
			ft_print_memory(temp);
			ft_putchar('\n');
			temp = temp->next;
		}
	}
	if (temp)
	{
	ft_putendl("map actuelle");
	ft_putstr("type  :");
	ft_putnbr(temp->type);
	ft_putstr("   ");
	ft_print_memory(temp);
	ft_putchar('\n');
	ft_print_memory(cast);
	ft_putchar('\n');
	ft_print_memory(cast + size);
	ft_putchar('\n');
	ft_bzero(ret, g_wall.block_size);
	}
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
	new = mmap(NULL, zone_size, FLAG_PROT, FLAG_MAP, -1, 0);
	if (new == (void *)-1)
		return (NULL);	
	if (type > 1)
		type = 3;
	map_it(new, type, zone_size);
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
				temp->left++;
				temp->size -= size;
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
	if (size <= 128)
		return (0);
	else if (size <= 1024)
		return (1);
	else
		return (size + g_wall.map_size + g_wall.block_size + 1);
}

void			check_align( void *ret, int size)
{
	if (((long)ret & 7) || !check(ret, NULL) )
	{
		ft_putstr("unalligned   ");
		ft_putnbr(size);
		ft_putstr("   -    ");
		ft_print_memory(ret);
		ft_putchar('\n');
	}
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
	size = ALIGN(size);
	ret = find_zone(type, size);
	check_align(ret, size);
	return (ret);
}

void			*calloc(size_t count, size_t size)
{
	void		*ret;

	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	size *= count;
	size = ALIGN(size);
	ft_bzero(ret, size);
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
	void		*ret;

	next = current->next;
	if (next && next->freed == 0)
	{
		current->size = size + next->size;
		current->next = next->next;
		ret = downsize(current, size);
	}
	else
	{
		ret = malloc(size);
		ft_memcpy(ret, current->ptr, size);
		free(current->ptr);
	}
	return (ret);
}

void			*realloc(void *ptr, size_t size)
{
	t_block		*current;
	void		*ret;

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
	size = ALIGN(size);
	if ((size_t)current->size == size)
		return (ptr);
	else if ((size_t)current->size > size)
		ret = downsize(current, size);
	else
		ret = upsize(current, size);
	check_align(ret, size);
	return (ret);
}
