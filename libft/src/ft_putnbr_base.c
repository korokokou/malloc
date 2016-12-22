/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:27:37 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 18:27:39 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_base(long int n, int div, char *s)
{
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n < div)
		write(1, &s[n], 1);
	else
	{
		ft_putnbr_base(n / div, div, s);
		ft_putnbr_base(n % div, div, s);
	}
}
