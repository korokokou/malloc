/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/16 00:53:24 by takiapo           #+#    #+#             */
/*   Updated: 2014/04/18 17:53:58 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t	index1;
	size_t	index2;

	index1 = 0;
	index2 = 0;
	while (s2[index2] && (index2 < n))
	{
		s1[index1] = s2[index2];
		index1++;
		index2++;
	}
	if (s2)
	{
		while (index1 < n)
		{
			s1[index1] = '\0';
			index1++;
		}
	}
	return (s1);
}
