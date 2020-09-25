/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_graph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:02:00 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/25 15:08:42 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		background_graph(t_visual *vis)
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
		SDL_RenderCopy(vis->rend, vis->tex, NULL, NULL);
		SDL_SetRenderDrawColor(vis->rend, 39, 0, 68, 255);
		SDL_RenderPresent(vis->rend);
	}
}

void		destroy_all_quit(t_visual *vis)
{
	SDL_DestroyRenderer(vis->rend);
	SDL_DestroyWindow(vis->win);
	SDL_Quit();
}