/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 22:05:03 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 16:57:47 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static int		ft_strncmp(const char *s1, const char *s2, int n)
{
	if (!*s1 && !*s2)
		return (0);
	while (n-- > 0 && (*s1 || *s2))
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

char			*ft_strstr(const char *s1, const char *s2)
{
	if (!*s2)
		return ((char*)s1);
	while (*s1)
	{
		if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
			return ((char *)s1);
		s1++;
	}
	return (0);
}
