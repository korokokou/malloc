/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:03:07 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/25 13:26:01 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/libft.h"

void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char		*s1temp;
	const char	*s2temp;

	s1temp = (char *)s1;
	s2temp = (char *)s2;
	while (n--)
		*s1temp++ = *s2temp++;
	return (s1);
}
