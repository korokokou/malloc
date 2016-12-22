/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 00:28:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 14:41:13 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_malloc	g_wall;

void			large_munmap(t_map *country)
{
	if (country)
	{
		if (country->prev)
			country->prev->next = country->next;
		if (country->next)
			country->next->prev = country->prev;
		if (g_wall.countries == country && g_wall.countries->next != NULL)
		{
			g_wall.countries = country->next;
			g_wall.countries->prev = NULL;
		}
		munmap(country, country->size);
	}
}

void			coalesce(t_map *country)
{
	t_block		*temp;
	t_block		*next;

	temp = country->region;
	while (temp)
	{
		if (temp->freed == 1)
		{
			next = temp->next;
			while (next && next->freed == 1)
			{
				temp->size += next->size;
				temp->next = next->next;
				next = next->next;
			}
		}
		temp = temp->next;
	}
}

void			check_free(t_map *country)
{
	t_block		*temp;

	if (country) 
	{
		temp = country->region;
		while (temp)
		{
			if (temp->freed == 0)
				break ;
			temp = temp->next;
		}
		if (temp == NULL)
			large_munmap(country);
	}
}

void			free(void *p)
{
	t_block		*temp;
	t_map		*country;
	char		*cast;

	if (!check(p, &country))
		return ;
	cast = p;
	cast -= g_wall.block_size;
	temp = (t_block *)cast;
	temp->freed = 1;
	coalesce(country);
	check_free(country);
}
