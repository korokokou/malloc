/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/08 20:13:35 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/13 17:04:48 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "includes/libft.h"

char	*ft_strtrim(const char *s)
{
	size_t	len;
	int		i;
	char	*ret;

	i = 0;
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
		len--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	len -= i;
	if (len == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (ret);
	while (len--)
		*ret++ = s[i++];
	if (ret)
		*ret = '\0';
	return (ret);
}
