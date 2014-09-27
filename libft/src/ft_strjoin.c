/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 21:22:04 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 17:12:10 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t		ft_strlen(const char *str)
{
	size_t			i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*p;
	char			*p2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	p = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	p2 = p;
	if (p == NULL)
		return (NULL);
	while (*s1)
	{
		*p++ = *s1;
		s1++;
	}
	while (*s2)
	{
		*p++ = *s2;
		s2++;
	}
	*p++ = '\0';
	return (p2);
}
