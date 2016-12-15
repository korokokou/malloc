/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo </var/mail/takiapo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:54:38 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/15 12:13:50 by takiapo          ###   ########.fr       */
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
