/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo </var/mail/takiapo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:34:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 08:32:11 by takiapo          ###   ########.fr       */
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

	if (ptr == NULL)
		return (malloc(size));
	if (!check(ptr, NULL))
	{
		ft_putendl("\ncheck ptr");
		show_alloc_mem();
		ft_print_memory(ptr);
		ft_putchar('\n');
		return (NULL);
	}
	if (size == 0)
	{
		free(ptr);
		return (find_zone(0, 0));
	}
	size = ALIGN(size);
	current = get_list(ptr);
	if ((size_t)current->size < size)
	{
		ret = upsize(current, size);
	}
	else if ((size_t)current->size > size + 32)
	{
		ret = downsize(current, size);
	}
	else
		ret = ptr;
	check(ret, NULL);
	return (ret);
}
