/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 22:05:03 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 17:00:02 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char			*ft_strnstr(const char *s1, const char *s2, int n)
{
	int	lengh2;

	lengh2 = ft_strlen(s2);
	if (!*s2)
		return ((char*)s1);
	while (n >= lengh2 && *s1)
	{
		if (ft_strncmp(s1, s2, lengh2) == 0)
			return ((char*)s1);
		s1++;
		n--;
	}
	return (0);
}
