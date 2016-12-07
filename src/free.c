/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 00:28:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/07 18:18:26 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_malloc	g_wall;

int				check(t_block *p, t_map **country)
{
	t_map		*temp;

	if (!p)
		return (0);
	temp = g_wall.countries;
	while (temp)
	{
		if (p >= temp->region && p <= temp->region + temp->size)
		{
			if (country)
				*country = temp;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void			large_munmap(t_map *country)
{
	if (country->prev)
		country->prev->next = country->next;
	if (country->next)
		country->next->prev = country->prev;
	if (g_wall.countries == country)
	{
		munmap(country, country->size);
		g_wall.countries = country;
		country->prev = NULL;
	}
}

void			other_munmap(t_map *country)
{
	t_map		*temp;

	temp = g_wall.countries;
	while (temp)
	{
		if (temp != country && country->type == temp->type)
		{
			large_munmap(country);
			break ;	
		}
			temp = temp->next;		
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
	country->left--;
	if (country->left <= 0)
		other_munmap(country);
	else if (country->type == 3)
		large_munmap(country);
}
