/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/23 10:52:12 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/15 17:13:50 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_malloc		g_wall = (t_malloc){0, 0, MAP_SIZE, BLOCK_SIZE};

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
		return (size + MAP_SIZE + BLOCK_SIZE);
}

int             check_align( void *ret, int size)
{
	if (((unsigned long)ret & 15) || !check(ret, NULL) )
	{
		ft_putendl("*************************************************");
		ft_putstr("unalligned   ");
		ft_putnbr(size);
		ft_putstr("   -    ");
		ft_print_memory(ret);
		ft_putchar('\n');
		ft_putnbr(g_wall.map_size);
		ft_putchar('\n');
		show_alloc_mem();
		//exit(-1);
		return (0);
	}
	(void)size;
	return (1);
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
	size = ALIGN(size);
	type = get_type_of_country(size);
	ret = find_zone(type, size);
	if (ret == NULL)
		ft_putendl("hum");
	check_align(ret, size);
		ft_putendl("*************************************************");
/*	show_alloc_mem();
	ft_print_memory(ret);
	ft_putstr("   ");
	ft_putnbr(size);
	ft_putchar('\n');
*/
	check(ret, NULL);
	return (ret);
}
