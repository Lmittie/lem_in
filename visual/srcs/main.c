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
	(data)->rooms_by_id = NULL;
	(data)->rooms_number = 0;
	(data)->start = -1;
	(data)->end = -1;
}

void	init_sdl(t_visual *vis)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		ft_putstr("SDL initialization error: ");
		ft_putstr(SDL_GetError());
		write(1, "\n", 1);
		exit(INIT_SDL_ERROR);
	}
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	if ((vis->win = SDL_CreateWindow("LEM IN VISUAL",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							WIDTH,
							HEIGHT,
							SDL_WINDOW_SHOWN)) == NULL)
	{
		ft_putstr("SDL_CreateWindow error: ");
		ft_putstr(SDL_GetError());
		write(1, "\n", 1);
		exit(INIT_SDL_ERROR);
	}
	vis->loop = false;
}

int		find_id_start_room(t_map_data data)
{
	t_room_list *cur;

	cur = data.rooms;
	while (cur->room_data->type != START)
		cur = cur->next;
	return (cur->room_data->id);
}

int		main()
{
	t_map_data	data;
	t_visual	vis;

	init_structure(&data);
	parse_map(&data);
	data.id_start_room = find_id_start_room(data);
	init_sdl(&vis);
	render_surface(&vis);
	parse_path(&data, &vis);
	check_coords(&data, &vis);
	background_graph(&vis, &data);
	destroy_all_quit(&vis);
	return (0);
}

