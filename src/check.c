/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:06:06 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 18:06:31 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern			t_malloc	g_wall;

int				is_it_mine(t_block *p, t_map *temp)
{
	t_block		*b_temp;

	b_temp = temp->region;
	while (b_temp)
	{
		if (b_temp == p)
			break ;
		b_temp = b_temp->next;
	}
	if (b_temp == NULL)
		return (0);
	return (1);
}

int				check(t_block *p, t_map **country)
{
	t_map		*temp;

	if (!p)
		return (0);
	temp = g_wall.countries;
	p = get_list(p);
	while (temp)
	{
		if ((long int)p >= (long int)temp->region
				&& (long int)p < (long int)temp->end)
		{
			if (country)
				*country = temp;
			return (is_it_mine(p, temp));
		}
		temp = temp->next;
	}
	return (0);
}
