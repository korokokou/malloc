/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo </var/mail/takiapo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 12:33:35 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 12:35:12 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern			t_malloc	g_wall;

int				is_it_mine(t_block *p, t_map *temp)
{
	t_block		*b_temp;

	b_temp = temp->region;
	while (b_temp)
	{
		if (b_temp == p)
			break;
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
		if ((long int)p >= (long int)temp->region && (long int)p < (long int)temp->end)
		{
			if (country)
				*country = temp;
			return (is_it_mine(p, temp));
		}
		temp = temp->next;
	}
	return (0);
}
