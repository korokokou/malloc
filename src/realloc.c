/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo </var/mail/takiapo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:34:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/15 11:57:05 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
		return (NULL);
	if (size == 0)
	{
		free(ptr);
		return (find_zone(0, 0));
	}
	current = get_list(ptr);
	size = ALIGN(size);
	if ((size_t)current->size == size)
		return (ptr);
	else if ((size_t)current->size > size)
		ret = downsize(current, size);
	else
		ret = upsize(current, size);
	return (ret);
}
