/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/24 00:30:43 by takiapo           #+#    #+#             */
/*   Updated: 2014/09/27 16:27:37 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_MALLOC_H
# define STRUCTS_MALLOC_H
typedef struct		s_block
{
	int				freed;
	int				size;
	struct s_block	*next;
	struct s_block	*back;
}					t_block;

typedef struct		s_malloc
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
	int				g_size;
}					t_malloc;
#endif /* !STRUCTS_MALLOC_H*/
