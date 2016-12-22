/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/18 18:20:49 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/29 03:43:03 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/structs.h"

void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char		*s1temp;
	const char	*s2temp;

	s1temp = (char *)s1;
	s2temp = (char *)s2;
	while (n--)
		*s1temp++ = *s2temp++;
	return (s1);
}

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;
	void		*data;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	else
	{
		if (content == NULL)
		{
			new->content = NULL;
			new->content_size = 0;
		}
		else
		{
			data = malloc(sizeof(char) * content_size + 1);
			if (!data)
				return (NULL);
			data = ft_memcpy(data, content, content_size);
			new->content = data;
			new->content_size = content_size;
		}
	}
	return (new);
}
