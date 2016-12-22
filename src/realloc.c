/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo </var/mail/takiapo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:34:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 08:22:20 by takiapo          ###   ########.fr       */
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

//	ft_putendl("upsize");
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
	{
		ft_putchar('\n');
		ft_putnbr(size);
		ft_putchar('\n');
		ft_putendl("ptr == NULL");
		return (malloc(size));
	}
	if (!check(ptr, NULL))
	{
		ft_putendl("check ptr");
		show_alloc_mem();
		ft_print_memory(ptr);
		ft_putchar('\n');
		return (NULL);
	}
	if (size == 0)
	{
		ft_putnbr(size);
		ft_putchar('\n');
	size = ALIGN(size);
		ft_putnbr(size);
		ft_putchar('\n');
	}
	if (size == 32)
	{
		free(ptr);
		ft_putendl("size == 0");
		return (find_zone(0, 0));
	}
	size = ALIGN(size);
	current = get_list(ptr);
	if ((size_t)current->size < size)
	{
		ft_putendl("upsize");
		ret = upsize(current, size);
	}
	else if ((size_t)current->size > size + 32)
	{
		ret = downsize(current, size);
		ft_putendl("downsize");
/*		ft_print_memory(current);
		ft_putstr("  ");
		ft_print_memory(ret);
		ft_putchar('\n');
*/
	}
	else
		ret = ptr;
	check(ret, NULL);
	ft_putendl("out");
	return (ret);
}
