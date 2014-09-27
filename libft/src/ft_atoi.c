/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:13:06 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 16:25:00 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int	number;
	int	signe;

	number = 0;
	signe = 1;
	while (*str == 32 || *str == 8 || *str == 9 || *str == 10
			|| *str == 11 || *str == 12 || *str == 13)
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			signe *= -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		number = number * 10 + *str++ - 48;
	}
	return (number * signe);
}
