/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 21:41:07 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/25 15:08:37 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "../SDL/include/SDL.h"
# include "../SDL/include/SDL_image.h"
# include <stdbool.h>
# include <time.h>
# include "../../libft/libft.h"

# define WIDTH	1000
# define HEIGHT	1000

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
	INVALID_LINKS = 3,
	INIT_SDL_ERROR = 4,
	SIMILAR_COORDS = 5
}				t_error_code;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_room_data
{
	t_point		coords;
	int			id;
	t_room_type	type;
	char		*name;
}				t_room_data;

typedef struct			s_room_list
{
	t_room_data			*room_data;
	struct s_room_list	*next;
}						t_room_list;

typedef struct		s_max_coords
{
	int				max_x;
	int				min_x;
	int				max_y;
	int				min_y;
}					t_max_coords;

typedef struct		s_map_data
{
	int				rooms_number;
	int				ants_num;
	int				**adjacency_matrix;
	int				start;
	t_room_list		*rooms;
	t_max_coords	max_coords;
	char 			**rooms_by_id;
	int				end;

}					t_map_data;

typedef struct		s_window
{
	int				x;
	int				y;
}					t_window;

typedef struct		s_visual
{
	t_window		size;
	int				delta_x;
	int				delta_y;
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		event;
	SDL_Surface		*surface;
	SDL_Texture		*tex;
	Uint32			render_flags;
	bool			run;
	
}					t_visual;

/*
** random.c
*/
int				random_number(int nbr_min, int nbr_max);
int				random_color();
void			draw_random_points(int nbr_points, bool randomize_color, SDL_Renderer *rend);


/*
** flow_color.c
*/
int				flow_color(int low, int high, int *flag, int myself);


/*
** all parse
*/
int				parse_ants_number(void);
void			parse_links(t_map_data *data);
void			parse_map(t_map_data *data);
void			parse_rooms(t_map_data *data);
t_room_type		check_if_comment(char **line, t_map_data *data);
int				size_of_matrix_rows(char **matrix);
void			free_delete_exit(char **line, char **splitted_line, int exit_num);
void			delete_splitted_line(char **splitted_line);
int				return_room_index(char *room_name, t_room_list *list);
void			add_link(char *line, t_map_data *data);
void			push_back_room(t_room_list **list, t_room_data *room_data,
							int *rooms_number);


/*
**	check_coords.c
*/
void			check_coords(t_map_data *data);


/*
** min_max_coords.c
*/
void			init_coord(t_room_list *root, t_map_data *data);
void			find_min_max(t_room_list *room, t_map_data *data);


/*
** fill_delta.c
*/
void			new_coords(t_map_data *data, t_visual *vis);

/*
** render_load_surface.c
*/
void			render_surface(t_visual *vis);

/*
** background_graph.c
*/
void			background_graph(t_visual *vis);
void			destroy_all_quit(t_visual *vis);


#endif