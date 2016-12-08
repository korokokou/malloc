/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 12:23:38 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/08 17:30:39 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_malloc		g_wall;

static void			ft_putnbr_base(long int n, int div, char *s)
{
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n < div)
		write(1, &s[n], 1);
	else
	{
		ft_putnbr_base(n / div, div, s);
		ft_putnbr_base(n % div, div, s);
	}
}

void				ft_print_memory(void *addr)
{
	long int		p;

	if (addr == NULL)
	{
		ft_putstr("(null)");
		return ;
	}
	p = (long int)addr;
	ft_putstr("0x");
	ft_putnbr_base(p, 16, "0123456789ABCDEF");
}
/*
static void			ft_putaddr(char *s, t_block *p)
{
	int				sum;

	sum = 0;
	ft_putstr(s);
	ft_print_memory(p);
	write(1, "\n", 1);
	while (p)
	{
		if (p->freed != 1)
		{
			ft_print_memory(p + g_wall->g_size / 16);
			write(1, " - ", 3);
			ft_print_memory(p->next);
			write(1, " : ", 3);
			ft_putnbr_base(p->size, 10, "0123456789");
			ft_putstr(" octects\n");
			sum += p->size;
		}
		p = p->next;
	}
	ft_putstr("Total : ");
	ft_putnbr_base(sum, 10, "0123456789");
	ft_putstr(" octects\n");
}
*/
void				show_alloc_mem(void)
{
	t_map			*temp;
	t_block			*truc;
	int i = 0;
	int	total = 0;
	
	temp = g_wall.countries;
	while (temp)
	{
		truc = temp->region;
		if (temp->type == 0)
			i++;
	 	if (temp->type  == 0)
			ft_putstr("tiny   ");
		else if (temp->type == 1)
			ft_putstr("small  ");
		else 
			ft_putstr("large  ");
		ft_putnbr(temp->size);
		ft_putchar('\n');
		int z = 0;
		total = 0;
		while (truc)
		{
			ft_print_memory(truc);
			ft_putstr("   -   ");
			ft_print_memory(truc->next);
			ft_putstr("   ");
			ft_putnbr(truc->size);
			ft_putstr("  ");
			if (truc->freed)
				ft_putendl("freed");
			else
				ft_putendl("useeeeeeeeeed");
			ft_putchar('\n');
			z++;
			total += truc->size;
			truc = truc->next;
			if (temp == temp->next)
				ft_putendl("merdE");
		}
		ft_putstr("nombre de zones = ");
		ft_putnbr(z);
		ft_putstr("  et ");
		ft_putnbr(temp->left);
		ft_putchar('\n');
		ft_putstr(" pour une taille de metadonnees de ");
		ft_putnbr(z * g_wall.block_size + g_wall.map_size);
		ft_putchar('\n');
		ft_putstr(" pour une taille en donnes de ");
		ft_putnbr(total);
		ft_putchar('\n');
		ft_putstr(" ce qui donne un tout de ");
		ft_putnbr(z * g_wall.block_size + g_wall.map_size + total);
			ft_putchar('\n');
		temp = temp->next;
	}
	ft_putstr(" nombres de zones de type 1: ");
	ft_putnbr(i);
	ft_putchar('\n');
}
