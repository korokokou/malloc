/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 00:28:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/11/25 10:37:13 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_malloc	g_wall;

int				check(t_block *p)
{
	t_map		*temp;

	if (!p)
		return (0);
	temp = g_wall.countries;
	while (temp)
	{
		if (p >= temp->region && p <= temp->region + temp->size)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void			free(void *p)
{
	t_block		*temp;
	int			i;

	if (!check(p))
		return ;
	i = sizeof(t_block);
	p -= i;
	temp = (t_block *)p;
	temp->freed = 1;
}
