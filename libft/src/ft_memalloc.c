/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 18:57:15 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/29 03:44:45 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void		*ft_memalloc(size_t size)
{
	void	*p;
	char	*p2;
	size_t	i;

	i = 0;
	p = (void *)malloc(sizeof(char) * size + 1);
	if (p == NULL)
		return (NULL);
	p2 = (char *)p;
	while (size-- > 1)
		p2[i++] = 0;
	return (p);
}
