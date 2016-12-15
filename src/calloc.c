/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo </var/mail/takiapo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 12:18:16 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/15 12:32:11 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*calloc(size_t count, size_t size)
{
	void		*ret;

	ret = malloc(count * size);
	if (!ret)
	{
		ft_putendl("problem");
		return (NULL);
	}
	size *= count;
	size = ALIGN(size);
	ft_bzero(ret, size);
	return (ret);
}
