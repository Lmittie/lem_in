/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:31:33 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/15 21:43:22 by lmittie          ###   ########.fr       */
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

typedef struct s_dinic_data
{
	int 			*ptr;
	int 			*distance;
	int				**capacity_matrix;
	int 			*queue;
	int 			start;
	int 			end;
	int 			n;
}				t_dinic_data;

typedef struct	s_data
{
	int				ants_num;
	int 			rooms_number;
	t_room_list		*rooms;
	int				**adjacency_matrix;
	int 			start;
	int 			end;
}				t_data;

int				dinic(t_data data);

/*
 * parse_map.c
 */
void 			parse_map(t_data *data);

int 			parse_ants_number();

void 			add_link(char *line, t_data *data);
void 			parse_links(t_data *data);

t_room_type		check_if_comment(char **line, t_data *data);
int 			size_of_matrix_rows(char **matrix);

t_room_data		*create_room(char *line, t_room_type room_type);
void 			parse_rooms(t_data *data);

/*
 * adjacency_matrix.c
 */
void 			init_matrix(int ***adjacency_matrix, int size);
void 			fill_adjacency_matrix(int index1, int index2, int ***adjacency_matrix, int size);

/*
 * deleting.c
 */
void			delete_splitted_line(char **splitted_line);

/*
 * room_list.c
 */
int 			return_room_index(char *room_name, t_room_list *list);
void 			push_back_room(t_room_list **list, t_room_data *room_data, int *rooms_number);

#endif
