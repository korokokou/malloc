/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/28 21:59:03 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_malloc				*g_wall = NULL;

void					*put_data(void *ret, int size, t_block *new, int state)
{
	t_block			data;

	if (g_wall->g_size == 0)
		g_wall->g_size = sizeof(t_block);
	(void)data;
	data.size = size;
	data.freed = state;
	if (new)
	{
		data.next = new->next;
		new->next = ret;
	}
	else
		data.next = NULL;
	data.back = new;
	if (new && new->next)
		new->next->back = ret;
	ret = memcpy(ret, (void *)(&data), g_wall->g_size);
	return (ret);
}

void					*initialize(t_block **list, int zone, t_block *temp)
{
	temp = *list;
	if (*list && zone > 0)
		return (temp = *list);
	temp = mmap(NULL, zone, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
			-1, 0);
	if (temp == (void *)-1)
		return (NULL);
	temp = put_data(temp, zone, temp, 1);
	if (!*list)
		*list = temp;
	return (temp);
}

void					*downsize(void *current, int size, int left)
{
	char			*next;
	t_block			*temp;

	next = (char *)current + size + g_wall->g_size;
	temp = (t_block *)current;
	if (left <= g_wall->g_size)
		size = temp->size;
	current = put_data(current, size, current, 0);
	if (left > g_wall->g_size)
		temp->next = put_data(next, left, current, 1);
	return (current);
}

void					*find_place(t_block *list, int size)
{
	int				j;
	t_block			*temp;

	j = 0;
	if (size > 0)
		temp = list;
	if (size < 0)
		return (list);
	while (temp)
	{
		if (temp->freed && temp->size - ABS(size) - g_wall->g_size >= 0)
			return (downsize(temp, size, temp->size - size - g_wall->g_size));
		j += (temp->size + g_wall->g_size);
		if (temp->next == NULL)
			list = temp;
		temp = temp->next;
	}
	list->next = initialize(&temp, j, temp);
	temp->back = list;
	return (find_place(list, size));
}

void					*malloc(size_t size)
{
	static size_t		i = 0;
	void				*back;
	t_block				*temp;

	temp = NULL;
	if (g_wall == NULL)
		initialise_first(&g_wall);
	if (g_wall == NULL)
		return (NULL);
	if (i == 0)
		i = getpagesize();
	if (size == 0 || i == 0)
		return (NULL);
	if (g_wall->g_size == 0)
		g_wall->g_size = sizeof(t_block);
	size = (((size - 1) >> 3) << 3) + 8;
	if (size <= 48)
		temp = initialize(&g_wall->tiny, i << 1, temp);
	else if (size > 48 && size <= 256)
		temp = initialize(&g_wall->small, i << 3, temp);
	else
		temp = large_malloc(&g_wall->large, (int *)&size, temp);
	if (temp == (void *)-1 || !(back = find_place(temp, size)))
		return (NULL);
	return (back + g_wall->g_size);
}
