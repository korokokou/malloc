/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 00:28:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/05 21:01:26 by takiapo          ###   ########.fr       */
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

void			free(void *p)
{
	t_block		*temp;
	t_map		*country;
	char		*cast;

	ft_putstr("free in:    ");
	if (!check(p, &country))
		return ;
	cast = p;
	cast -= g_wall.block_size;
	temp = (t_block *)cast;
	ft_print_memory(cast);	
	ft_putchar('\n');
	temp->freed = 1;
	country->left--;
	ft_putendl("free out");
}
