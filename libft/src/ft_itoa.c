/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 14:25:06 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 17:04:32 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*itoa_script(char *p, int n)
{
	if (n == 0)
	{
		*p = '0';
		p--;
	}
	while (n != 0)
	{
		*p = (n % 10 + 48);
		if (n < 0)
			*p = *p - 2 * (n % 10);
		n /= 10;
		p--;
	}
	return (p);
}

char		*ft_itoa(int n)
{
	char	*p;

	p = (char *)malloc(13 * (sizeof(char*)));
	if (p == NULL)
		return (NULL);
	p += 13;
	*p = '\0';
	p--;
	p = itoa_script(p, n);
	if (n < 0)
		*p = '-';
	else
		p++;
	return (p);
}
