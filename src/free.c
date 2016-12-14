/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 00:28:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/14 16:28:06 by takiapo          ###   ########.fr       */
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
		g_wall.countries = country->next;
		g_wall.countries->prev = NULL;
	}
		munmap(country, country->size);
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
				country->left--;
			}
		}
		temp = temp->next;
	}
}

void			check_free(t_map *country)
{
	t_block		*temp;

	temp = country->region;
	while (temp)
	{
		if (temp->freed == 0)
			break;
		temp = temp->next;
	}
	if (temp == NULL)	
		large_munmap(country);
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
	coalesce(country);
	if (country->left <= 0)
		other_munmap(country);
	else if (country->type == 3)
		large_munmap(country);
}
