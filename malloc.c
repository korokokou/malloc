/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/24 18:44:13 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/malloc.h"

t_block		*g_tiny_malloc = NULL;
t_block		*g_small_malloc = NULL;
t_block		*g_large_malloc = NULL;
int			g_size = 0;

void				*put_data(void *ret, int size, t_block *new, int state)
{
	t_block			data;

	g_size = sizeof(t_block);
	(void)data;
	data.size = size;
	data.freed = state;
	data.next = new->next;
	data.back = new;
	new->next = ret;
	if (new->next)
		new->next->back = ret;
	ret = memcpy(ret , (void *)(&data), g_size);
	return (ret);
}

void				*initialize(t_block **list, int zone, t_block *temp)
{
	t_block			data;
	t_block			*t_mp;

	if (*list && zone > 0)
		return (temp = *list);
	if (zone < 0 && *list)
	{
		t_mp = *list;
		while (t_mp && (t_mp->freed = 0) && t_mp->next)
			t_mp = temp->next;
		t_mp->next = initialize(&temp, -zone, temp);
		return (temp);
	}
	if (zone < 0)
		zone *= -1;
	(void)data;
	*list = mmap(NULL, zone, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
			-1, 0);
	if (*list == (void *) -1)
		return (NULL);
	data.size = zone;
	data.freed = 1;
	data.next = NULL;
	data.back = NULL;
	*list = memcpy(*list, (void *)(&data), g_size);
	temp = *list;
	return (*list);
}

void				*downsize(t_block *current, int size, int left)
{
	if (left < g_size)
		size = current->size;
	current = put_data(current, size, current, 0);
	if (left > g_size)
		current->next = put_data(current + size + g_size, left, current, 1);
	return (current);
}

void				*make_malloc(t_block *list, int size)
{
	int				j;
	t_block			*temp;

	j = 0;
	temp = list;
	if (size < 0)
		return (temp);
	while (temp)
	{
		if (temp->freed  && temp->size - size - g_size > 0)
			return (downsize(temp, size, temp->size - size - g_size));
		j += temp->size + g_size;
		if (temp->next == NULL)
			list = temp;
		temp = temp->next;
	}
	list->next = initialize(&temp, j, temp);
	temp->back = list;
	return (make_malloc(list, size));
}

void					*my_malloc(size_t size)
{
	static size_t		i = 0;
	void 				*back;
	t_block				*temp;

	temp = NULL;
	if (i == 0)
		i = getpagesize();
	if(size == 0 || i == 0)
		return (NULL);
	if (g_size == 0)
		g_size = sizeof(t_block);
	size = (((size - 1) >> 3) << 3) + 8;
	if (size <= 48)
		temp = initialize(&g_tiny_malloc, i << 1, temp);
	else if (size > 48 && size <= 256)
		temp = initialize(&g_small_malloc, i << 3, temp);
	else
		temp = initialize(&g_large_malloc, size = -size, temp);
	if (temp == (void *) -1 || !(back = make_malloc(temp, size)))
		return (NULL);
	return (back + 24);
}
