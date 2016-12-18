/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo </var/mail/takiapo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:34:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/15 17:14:48 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_malloc g_wall;

void			*reallocf(void *ptr, size_t size)
{
	void		*ret;

	ret = realloc(ptr, size);
	if (ret != ptr)
		free(ptr);
	return (ret);
}

t_block			*get_list(void *ptr)
{
	t_block		*ret;
	char		*cast;

	cast = ptr;	
	cast -= BLOCK_SIZE;
	ret = (t_block *)cast;
	return (ret);
}

void			*upsize(t_block *current, size_t size)
{
	t_block		*next;
	void		*ret;

	ft_putendl("upsize");
	next = current->next;
	if (next && next->freed == 0)
	{
		if (current->size + next->size + 32 > (int)size)
		{
			current->size += next->size;
			current->next = next->next;
			ret = downsize(current, size);
			if (ret != NULL)
				return (ret);
		}
	}
	ret = malloc(size);
	ft_memcpy(ret, current->ptr, current->size);
	free(current->ptr);
	return (ret);
}

void			*realloc(void *ptr, size_t size)
{
	t_block		*current;
	void		*ret;

	ft_putendl("realloc");
	if (ptr == NULL)
		return (malloc(size));
	if (!check(ptr, NULL))
		return (NULL);
	if (size == 0)
	{
		free(ptr);
		return (find_zone(0, 0));
	}
	current = get_list(ptr);
	size = ALIGN(size);
		ft_print_memory(current);
		ft_putchar('\n');
	if ((size_t)current->size == size)
	{
		ft_putendl("egalite");
		return (ptr);
	}
	else if ((size_t)current->size > size)
	{
/*		ft_putstr("downsize   ");
		ft_putnbr(current->size);
		ft_putstr("   ");
		ft_putnbr(size);
		ft_putchar('\n');
		show_alloc_mem();
*/	
		ret = downsize(current, size);
		ft_print_memory(current);
		ft_putstr("  ");
		ft_print_memory(ret);
		ft_putchar('\n');
	}
	else
		ret = upsize(current, size);
	check(ret, NULL);
	ft_putendl("out");
	return (ret);
}