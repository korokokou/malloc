/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 00:28:26 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/27 13:27:18 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/malloc.h"

extern	t_block	*g_tiny_malloc;
extern	t_block	*g_small_malloc;
extern	t_block	*g_large_malloc;

void			free_large(t_block *p, int size)
{
	if (p == g_large_malloc)
		g_large_malloc = p->next;
	if (p->back)
		p->back->next = p->next;
	if (p->next)
		p->next->back = p->back;
	munmap(p, size);
}

void			free_less(t_block *p)
{
	t_block		*temp;

	temp = p;
	if (temp->next && temp->next->freed == 1)
	{
		temp->next = temp->next->next;
		temp->next->next->back = temp;
		temp->size += temp->next->size;
	}
	if (p == g_small_malloc)
		g_small_malloc = p->next;
	if (p == g_tiny_malloc)
		g_tiny_malloc = p->next;
	if (temp->back && temp->back->freed == 1)
	{
		temp->back->next = p->next;
		temp->back->size += p->size;
	}
	temp->freed = 1;
	if (!g_small_malloc && !temp->back && p->size == getpagesize() * 2)
		munmap(p, p->size);
	if (!g_tiny_malloc && !temp->back && p->size == getpagesize() * 8)
		munmap(p, p->size);
	p = NULL;
}

void			free(void	*p)
{
	t_block 	*temp;
	int			i;

	i = sizeof(t_block);
	p -= i;
	if (p)
	{
		temp = (t_block *)p;
		if (temp->size > 256)
			free_large(p, temp->size + i);
		else
			free_less(p);
	}
	else
	{
		ft_putstr("error\n");
		return ;
	}
}