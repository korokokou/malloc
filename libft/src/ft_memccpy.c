/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:03:07 by takiapo           #+#    #+#             */
/*   Updated: 2014/04/15 18:52:43 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void			*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	char		*s1temp;
	const char	*s2temp;

	s1temp = (char *)s1;
	s2temp = (const char *)s2;
	while (n-- != 0)
	{
		*s1temp = *s2temp;
		if ((unsigned char)*s1temp == (unsigned char)c)
			return (void *)(s1temp + 1);
		s1temp++;
		s2temp++;
	}
	return (NULL);
}
