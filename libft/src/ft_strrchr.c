/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 20:35:35 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 16:50:59 by takiapo          ###   ########.fr       */
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

char			*ft_strrchr(const char *s, int c)
{
	const char	*last;

	if (!*s)
		return (0);
	last = s + ft_strlen(s);
	while (*s)
	{
		if (*s == c)
			last = s;
		s++;
	}
	if (*last == c)
		return ((char*)last);
	return (0);
}
