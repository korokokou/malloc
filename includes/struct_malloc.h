/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_malloc.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takiapo <takiapo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/28 22:06:33 by takiapo           #+#    #+#             */
/*   Updated: 2016/12/06 18:40:32 by takiapo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_MALLOC_H
# define STRUCT_MALLOC_H

# define TINY 0
# define SMALL 1
# define LARGE 2

typedef struct		s_block
{
	struct s_block	*next;
	void			*ptr;
	int				freed;
	int				size;
	char			data[1];
}					t_block;

typedef struct		s_map
{
	t_block			*region;
	size_t			size;
	int				type;
	int				left;
	void 			*start;
	struct s_map	*next;
	struct s_map	*prev;
}					t_map;

typedef struct		s_malloc
{
	t_map			*countries;
	int				page_size;
	int				map_size;
	int				block_size;
}					t_malloc;
#endif
