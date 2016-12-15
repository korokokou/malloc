/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo </var/mail/takiapo>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 11:53:39 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/15 11:54:01 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_print_memory(void *addr)
{
	long int		p;

	if (addr == NULL)
	{
		ft_putstr("(null)");
		return ;
	}
	p = (long int)addr;
	ft_putstr("0x");
	ft_putnbr_base(p, 16, "0123456789ABCDEF");
}
