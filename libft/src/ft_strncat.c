/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 17:54:29 by takiapo           #+#    #+#             */
/*   Updated: 2013/12/11 11:43:55 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char		*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*s1temp;

	if (!*s2)
		return (s1);
	s1temp = s1 + ft_strlen(s1);
	while (n-- && *s2)
		*s1temp++ = *s2++;
	*s1temp++ = '\0';
	return (s1);
}
