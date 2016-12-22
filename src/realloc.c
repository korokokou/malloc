/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo </var/mail/takiapo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:34:26 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 17:45:26 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern t_malloc g_wall;
pthread_mutex_t	g_malloc_lock;

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

	pthread_mutex_lock(&g_malloc_lock);
	if (ptr == NULL)
		return (malloc(size));
	if (!check(ptr, NULL))
		return (NULL);
	if (size == 0)
	{
		free(ptr);
		return (find_zone(0, 0));
	}
	size = ALIGN(size);
	current = get_list(ptr);
	if ((size_t)current->size < size)
		ret = upsize(current, size);
	else if ((size_t)current->size > size + 32)
		ret = downsize(current, size);
	else
		ret = ptr;
	pthread_mutex_unlock(&g_malloc_lock);
	return (ret);
}
