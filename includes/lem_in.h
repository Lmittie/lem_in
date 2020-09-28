/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:31:33 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/28 20:28:04 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdio.h>

# define INF 1000000000

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
	size_t		input_id;
	size_t		output_id;
	size_t		id;
	t_room_type	type;
	char		*name;
}				t_room_data;

typedef struct	s_room_list
{
	t_room_data			*room_data;
	struct s_room_list	*next;
}				t_room_list;

typedef struct	s_path
{
	int 			id;
	struct s_path	*next;
}				t_path;

typedef struct	s_paths
{
	t_path			*id_list;
	int 			path_len;
	int 			ants_num;
	int				*ants_by_id;
	int				last_ant_id;
	int 			output_lines;
	struct s_paths	*next;
	struct s_paths	*prev;
}				t_paths;

typedef struct	s_dinic_data
{
	int				*ptr;
	int				*distance;
	int 			**flow_matrix;
	int				*queue;
	int				start;
	int				end;
	int				n;
}				t_dinic_data;

typedef struct	s_data
{
	int				ants_num;
	int 			id_counter;
	int				rooms_number;
	char 			**rooms_by_id;
	int 			*direction_id;
	t_room_list		*rooms;
	t_paths			*paths;
	int				**adjacency_matrix;
	int				start;
	int				end;
}				t_data;

void			init_structure(t_data *data);

void 			find_best_path(t_paths **best_paths,
					   t_dinic_data *data,
					   int ants_num,
					   const int *dir_id);

void 			add_path(t_paths **paths, t_path *path, int path_length);

void			print_ants(t_data *data);

int				count_ants_on_each_path(t_paths **paths, int ants_num);

t_paths			*dinic(t_data *data);

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
void			fill_adjacency_matrix(t_room_data *room1,
							 t_room_data *room2,
							 int ***adjacency_matrix,
							 int size);

/*
 * deleting.c
 */
void			delete_splitted_line(char **splitted_line);
void			free_delete_exit(char **line, char **splitted_line, int exit_num);

/*
 * room_list.c
 */
t_room_data		*return_room(char *room_name, t_room_list *list);
void			push_back_room(t_room_list **list, t_room_data *room_data, int *id_counter);

#endif
