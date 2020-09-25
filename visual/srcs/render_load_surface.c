/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_load_surface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:58:09 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/25 15:00:54 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		render_surface(t_visual *vis)
{
	vis->render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	vis->rend = SDL_CreateRenderer(vis->win, -1, vis->render_flags);
	vis->surface = SDL_LoadBMP("images/dog.bmp");
	vis->tex = SDL_CreateTextureFromSurface(vis->rend, vis->surface);
	SDL_FreeSurface(vis->surface);
	SDL_RenderClear(vis->rend);
	vis->run = true;
}