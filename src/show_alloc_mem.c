/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 12:23:38 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 18:04:09 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_malloc		g_wall;

void				print_map(t_block *truc, int *total)
{
	while (truc)
	{
		if (truc->freed == 0)
		{
			ft_print_memory(truc);
			ft_putstr(" - ");
			ft_print_memory(truc->next);
			ft_putstr(" : ");
			ft_putnbr(truc->size);
			ft_putstr(" octects\n");
			*total += truc->size;
		}
		truc = truc->next;
	}
}

void				show_alloc_mem(void)
{
	t_map			*temp;
	int				total;

	total = 0;
	temp = g_wall.countries;
	while (temp)
	{
		if (temp->type == 0)
			ft_putstr("TINY  : ");
		else if (temp->type == 1)
			ft_putstr("SMALL : ");
		else
			ft_putstr("LARGE : ");
		ft_print_memory(temp);
		ft_putchar('\n');
		print_map(temp->region, &total);
		temp = temp->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putchar('\n');
}
