/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 21:04:57 by takiapo           #+#    #+#             */
/*   Updated: 2014/04/15 18:33:58 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*p;
	char	*p2;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	p = (char *)malloc(len * sizeof(char) + 1);
	p2 = p;
	if (p == NULL)
		return (NULL);
	while (*s)
	{
		if (i >= start && i < start + len)
		{
			*p = *s;
			p++;
		}
		s++;
		i++;
	}
	*p++ = '\0';
	return (p2);
}
