/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_graph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:02:00 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/25 20:59:48 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

int			find_coord_by_name(t_map_data *data, int id, char c)
{
	t_room_list *room;

	room = data->rooms;
	while (room->room_data->id != id)
	{
		room = room->next;
	}
	return (c == 'x' ? room->room_data->coords.x : room->room_data->coords.y);
}

int			find_name(int **matrix, int *i, int *j, int count)
{
	int n;
	int m;

	n = (*i);
	m = (*j);
	while (n < count)
	{
		while (m < count)
		{
			if (matrix[n][m])
			{
				(*i) = n;
				(*j) = m;
				return (1);
			}
			m++;
		}
		n++;
		m = 0;
	}
	return (0);
}

void		draw_links(t_visual *vis, t_map_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	SDL_SetRenderDrawColor(vis->rend, 100, 100, 100, 255);
	while (find_name(data->adjacency_matrix, &i, &j, data->rooms_number))
	{
		if (j == (data->rooms_number - 1))
		{
			i++;
			j = 0;
		}
		else
			j++;
		vis->line.x1 = find_coord_by_name(data, i, 'x');
		vis->line.y1 = find_coord_by_name(data, i, 'y');
		vis->line.x2 = find_coord_by_name(data, j, 'x');
		vis->line.y2 = find_coord_by_name(data, j, 'y');
		SDL_RenderDrawLine(vis->rend,	vis->line.x1,
										vis->line.y1,
										vis->line.x2,
										vis->line.y2);
	}
}

void		draw_node(t_visual *vis, t_map_data *data)
{
	t_room_list *room;

	room = data->rooms;
	SDL_SetRenderDrawColor(vis->rend, 255, 255, 255, 255);
	while(room != NULL)
	{
		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x,
										room->room_data->coords.y);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x - 1,
										room->room_data->coords.y - 1);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x - 1,
										room->room_data->coords.y);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x,
										room->room_data->coords.y - 1);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x - 1,
										room->room_data->coords.y + 1);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x + 1,
										room->room_data->coords.y - 1);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x + 1,
										room->room_data->coords.y);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x,
										room->room_data->coords.y + 1);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x + 1,
										room->room_data->coords.y + 1);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x + 2,
										room->room_data->coords.y);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x - 2,
										room->room_data->coords.y);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x,
										room->room_data->coords.y + 2);

		SDL_RenderDrawPoint(vis->rend,	room->room_data->coords.x,
										room->room_data->coords.y - 2);
		room = room->next;
	}
}

void		background_graph(t_visual *vis, t_map_data *data)
{
	while (vis->run)
	{
		while (SDL_PollEvent(&(vis->event)))
		{
			if (vis->event.type == SDL_QUIT)
				vis->run = false;
			if (vis->event.type == SDL_KEYUP)
				vis->run = false;
		}
		// SDL_RenderCopy(vis->rend, vis->tex, NULL, NULL);
		SDL_SetRenderDrawColor(vis->rend, 39, 0, 68, 255);
		SDL_RenderClear(vis->rend);
		SDL_SetRenderDrawColor(vis->rend, 255, 255, 255, 255);
		draw_links(vis, data);
		// draw_node(vis, data);
		SDL_RenderPresent(vis->rend);
	}
}

void		destroy_all_quit(t_visual *vis)
{
	SDL_DestroyRenderer(vis->rend);
	SDL_DestroyWindow(vis->win);
	SDL_Quit();
}