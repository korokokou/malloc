/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:05:47 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 18:05:49 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t	g_malloc_lock;

void			*calloc(size_t count, size_t size)
{
	void		*ret;

	pthread_mutex_lock(&g_malloc_lock);
	ret = malloc(count * size);
	if (!ret)
	{
		ft_putendl("problem");
		return (NULL);
	}
	size *= count;
	size = ALIGN(size);
	ft_bzero(ret, size);
	pthread_mutex_unlock(&g_malloc_lock);
	return (ret);
}
