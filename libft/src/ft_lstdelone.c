/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/13 17:16:39 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/14 21:27:17 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdlib.h>
#include "../includes/structs.h"

void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;

	temp = *alst;
	if (temp)
	{
		(*del)(temp->content, temp->content_size);
		free (temp);
		*alst = NULL;
		temp = *alst;
	}
}
