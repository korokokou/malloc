/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 09:39:28 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/07 18:25:56 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "includes/libft.h"
void				ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
//	int	i = 0;
	p = s;
	while (n)
	{
/*		i++;
		ft_putstr(" ");
		ft_putnbr(i);
	ft_putchar('\n');
*/
		*p = '\0';
		p++;
		n--;
	}
}
