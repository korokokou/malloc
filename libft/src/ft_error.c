/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/29 03:31:32 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/29 03:47:35 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/libft.h"

int			ft_error(char *str)
{
	if (str)
		ft_putstr(str);
	else
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}
