/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:05:59 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 16:41:10 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

static size_t		ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void				ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}
