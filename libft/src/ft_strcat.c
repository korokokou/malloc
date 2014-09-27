/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 17:54:29 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/14 21:28:08 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char			*ft_strcat(char *s1, const char *s2)
{
	int			length1;
	int			length2;

	length1 = ft_strlen(s1);
	length2 = 0;
	while (length2 < ft_strlen(s2))
		s1[length1++] = s2[length2++];
	s1[length1++] = '\0';
	return (s1);
}
