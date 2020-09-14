/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:31:33 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/14 20:27:40 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

#include <stdio.h>

typedef enum	e_room_type
{
	START,
	END,
	DEFAULT,
	PARSE_ERROR
}				t_room_type;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_room_data
{
	t_point		coords;
	size_t		id;
	t_room_type	type;
	char		*name;
}				t_room_data;

typedef struct	s_room_list
{
	t_room_data			*room_data;
	struct s_room_list	*next;
}				t_room_list;

typedef struct	s_data
{
	int				ants_num;
	int 			rooms_number;
	t_room_list		*rooms;
	int				**adjacency_matrix;
	int 			start;
	int 			end;
}				t_data;

/*
 * parse_map.c
 * */
void 	parse_map(t_data *data);

/*
 * deleting.c
 */
void			delete_splitted_line(char **splitted_line);

void 			create_room_list(t_room_list **list, t_room_data *room_data);
void 			push_back_room(t_room_list **list, t_room_data *room_data, int *rooms_number);

#endif
