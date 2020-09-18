/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:31:33 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/18 19:57:54 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdio.h>

# define WIN_X 1000
# define WIN_Y 1000

typedef enum	e_room_type
{
	START,
	END,
	DEFAULT,
	PARSE_ERROR
}				t_room_type;

typedef enum	e_exit_code
{
	MALLOC_ERROR = 10,
	INVALID_ANTS = 1,
	INVALID_ROOMS = 2,
	INVALID_LINKS = 3
}				t_exit_code;

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

typedef struct	s_path_data
{
	int		length;
	int		*path;
	int 	ants;
	int 	*ants_by_id;
	int 	last_ant_id;
	int 	dist_from_end;
}				t_path_data;

typedef struct	s_path_list
{
	t_path_data			*path_data;
	struct s_path_list	*next;
}				t_path_list;

typedef struct	s_dinic_data
{
	int				*ptr;
	int				*room_entry;
	int				*distance;
	int				**capacity_matrix;
	int				*queue;
	int				start;
	int				end;
	int				n;
}				t_dinic_data;

typedef struct	s_data
{
	int				ants_num;
	int				rooms_number;
	char 			**rooms_by_id;
	t_room_list		*rooms;
	t_path_list		*paths;
	int				**adjacency_matrix;
	int				start;
	int				end;
	int 			max_flow;
}				t_data;

void			print_ants(t_data *data);

void			count_ants_on_each_path(t_data *data);

int				dinic(t_data *data);

/*
 * parse_map.c
 */
void			parse_map(t_data *data);

int				parse_ants_number(void);

void			add_link(char *line, t_data *data);
void			parse_links(t_data *data);

t_room_type		check_if_comment(char **line, t_data *data);
int				size_of_matrix_rows(char **matrix);

t_room_data		*create_room(char *line, t_room_type room_type);
void			parse_rooms(t_data *data);

/*
 * adjacency_matrix.c
 */
void			init_matrix(int ***adjacency_matrix, int size);
void			fill_adjacency_matrix(int index1, int index2, int ***adjacency_matrix, int size);
void			copy(int **dst, int **src, int size);

/*
 * deleting.c
 */
void			delete_splitted_line(char **splitted_line);
void			free_delete_exit(char **line, char **splitted_line, int exit_num);

/*
 * room_list.c
 */
int				return_room_index(char *room_name, t_room_list *list);
void			push_back_room(t_room_list **list, t_room_data *room_data, int *rooms_number);

/*
* visual/
*/
void		make_visual(t_data data);

#endif
