/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/08 19:43:15 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 17:11:23 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static char		*ft_strcpy(char *s1, const char *s2)
{
	int			i;

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

static int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char			*get_s(char *s, char c)
{
	while (*s != '\0' && *s != c)
		s++;
	*s = '\0';
	return (s);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**young_link;
	char		**link;
	char		*sword;

	if (s == NULL)
		return (NULL);
	sword = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	link = (char **)malloc(sizeof(char *) * ft_strlen(s) / 2 + 1);
	sword = ft_strcpy(sword, s);
	if (sword == NULL || link == NULL)
		return (NULL);
	young_link = link;
	while (*sword)
	{
		if (*sword != c && *sword != '\0')
		{
			*link++ = sword;
			sword = get_s(sword, c);
		}
		sword++;
	}
	return (young_link);
}
