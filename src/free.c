/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 00:28:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/18 18:10:58 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_malloc	g_wall;
extern int	count;

int				check(t_block *p, t_map **country)
{
	t_map		*temp;
	t_block		*b_temp;
	t_block		*cast;

	if (!p)
		return (0);
	temp = g_wall.countries;
	while (temp)
	{
		if (p >= temp->region && p <= temp->region + temp->size)
		{
			b_temp = temp->region;
			cast = get_list(p);
			while (b_temp)
			{
				if (b_temp == cast)
					break;
				b_temp = b_temp->next;
			}
			if (b_temp == NULL)
				ft_putendl("NULL");
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
	if (country)
	{
		if (country->prev)
			country->prev->next = country->next;
		if (country->next)
			country->next->prev = country->prev;
		if (g_wall.countries != NULL
			&& g_wall.countries == country
			&& g_wall.countries->next != NULL)
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
				country->left--;
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
	count--;
	ft_putnbr(count);
	ft_putchar ('\n');
	cast = p;
	cast -= g_wall.block_size;
	temp = (t_block *)cast;
	temp->freed = 1;
	country->left--;
	ft_putendl("coalesce");
	coalesce(country);
	ft_putendl("check_free");
	check_free(country);
	ft_putendl("out");
}
