/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 17:54:29 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 17:00:29 by takiapo          ###   ########.fr       */
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

int				ft_strlcat(char *dst, const char *src, int size)
{
	int		n;
	int		length1;
	int		length2;
	int		count;

	count = 0;
	length1 = ft_strlen(dst);
	length2 = ft_strlen(src);
	dst = dst + length1;
	n = size - length1 - 1;
	while (n-- > 0 && size-- > 0)
	{
		if (*src == '\0')
			count++;
		*dst++ = *src++;
	}
	if (size > 0)
		*dst++ = '\0';
	if (count > 0)
		return (length1 + length2);
	return (size);
}
