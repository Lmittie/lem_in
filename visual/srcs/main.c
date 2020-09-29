// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:08:37 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/21 16:20:37 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void	init_structure(t_map_data *data)
{
	(data)->ants_num = -1;
	(data)->adjacency_matrix = NULL;
	(data)->rooms = NULL;
	(data)->rooms_number = 0;
	(data)->start = -1;
	(data)->end = -1;
}

void	init_sdl(t_visual *vis)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		ft_putstr("SDL initialization error:");
		ft_putstr(SDL_GetError());
		exit(INIT_SDL_ERROR);
	}
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	vis->win = SDL_CreateWindow("LEM IN VISUAL",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							WIDTH,
							HEIGHT,
							SDL_WINDOW_SHOWN);
}

int		main()
{
	t_map_data	data;
	int			i;
	int			j;
	t_visual	vis;

	i = 0;
	j = 0;
	init_structure(&data);
	parse_map(&data);
	parse_path(&data, &vis);

	check_coords(&data);
	new_coords(&data, &vis);
	init_sdl(&vis);
	render_surface(&vis);
	background_graph(&vis, &data);
	destroy_all_quit(&vis);

	printf("rooms_number = %d\n", data.rooms_number);
	printf ("delta_x = %d		delta_y = %d\n", vis.delta_x, vis.delta_y);
	while (data.rooms != NULL)
	{
		printf("NAME = %s	ID = %d		X_CORD = %d		Y_CORD = %d\n",
					data.rooms->room_data->name,
					data.rooms->room_data->id,
					data.rooms->room_data->coords.x,
					data.rooms->room_data->coords.y);
		data.rooms = data.rooms->next;		
	}
	printf ("X = (max, min) = (%d; %d)		Y = (max, min) = (%d; %d)\n",
					data.max_coords.max_x,
					data.max_coords.min_x,
					data.max_coords.max_y,
					data.max_coords.min_y);
	return (0);
}

