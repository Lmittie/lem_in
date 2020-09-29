/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_graph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:02:00 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/29 19:37:05 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		background_graph(t_visual *vis, t_map_data *data)
{
	int w;
	int h;

	while (vis->run)
	{
		while (SDL_PollEvent(&(vis->event)))
		{
			if (vis->event.type == SDL_QUIT)
				vis->run = false;
			if (vis->event.type == SDL_KEYUP)
				vis->run = false;
		}
		SDL_SetRenderDrawColor(vis->rend, 39, 0, 68, 255);
		SDL_RenderClear(vis->rend);
		draw_links(vis, data);
		draw_node(vis, data);

		vis->pos.x = (data->rooms->room_data->coords.x - (vis->size_node * 2));
		vis->pos.y = (data->rooms->room_data->coords.y - (vis->size_node * 2));
		SDL_QueryTexture(vis->tex, NULL, NULL, &(vis->pos.w), &(vis->pos.h));
		vis->pos.w = vis->size_node * 5;
		vis->pos.h = vis->size_node * 4;
		SDL_RenderCopy(vis->rend, vis->tex, NULL, &(vis->pos));

		SDL_RenderPresent(vis->rend);
	}
}

void		destroy_all_quit(t_visual *vis)
{
	SDL_DestroyRenderer(vis->rend);
	SDL_DestroyWindow(vis->win);
	SDL_Quit();
}