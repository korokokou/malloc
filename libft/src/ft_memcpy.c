/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:03:07 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/14 14:39:03 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/libft.h"

void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char		*s1temp;
	const char	*s2temp;
	size_t		i;

	s1temp = (char *)s1;
	s2temp = (char *)s2;
	i = 0;
	while (i < n)
	{
		s1temp[i] = s2temp[i];
		i++;
	}
	return (s1);
}
