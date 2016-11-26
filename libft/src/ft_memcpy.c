/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:03:07 by takiapo           #+#    #+#             */
/*   Updated: 2016/11/26 13:56:13 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/libft.h"

void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char		*s1temp;
	const char	*s2temp;

	s1temp = (char *)s1;
	s2temp = (char *)s2;
	while (n)
	{
		s1temp[n] = s2temp[n];
		n--;
	}
	return (s1);
}
