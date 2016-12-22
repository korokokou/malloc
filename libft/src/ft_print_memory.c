/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 18:27:19 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/22 18:27:21 by takiapo          ###   ########.fr       */
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
