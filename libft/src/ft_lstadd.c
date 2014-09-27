/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/13 17:26:25 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/14 21:26:55 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/structs.h"

void		ft_lstadd(t_list **alst, t_list *new)
{
	if (new)
		new->next = *alst;
	*alst = new;
	return ;
}
