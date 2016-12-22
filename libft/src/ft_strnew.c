/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 17:48:23 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/29 03:37:47 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	char	*p;
	char	*p2;

	p = (char *)malloc(sizeof(char) * size);
	if (p == NULL)
		return (NULL);
	p2 = p;
	while (size--)
		*p++ = '\0';
	return (p2);
}
