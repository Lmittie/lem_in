/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_load_surface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:58:09 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/03 18:13:15 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		render_surface(t_map_data *data, t_visual *vis)
{
	vis->render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_TEXTUREMODULATE_ALPHA;
	if ((vis->rend = SDL_CreateRenderer(vis->win, -1, vis->render_flags)) == NULL)
	{
		ft_putstr("SDL_CreateRender error: ");
		ft_putstr(SDL_GetError());
		write(1, "\n", 1);
		free_data(data);
		exit(CREATE_RENDER);
	}
	if ((vis->surface = IMG_Load("images/back_gradient3.png")) == NULL)
	{
		ft_putstr("SDL_CreateSurface error: ");
		ft_putstr(SDL_GetError());
		write(1, "\n", 1);
		free_data(data);
		exit(CREATE_SURFACE);
	}
	if ((vis->back = SDL_CreateTextureFromSurface(vis->rend, vis->surface)) == NULL)
	{
		ft_putstr("SDL_CreateRender error: ");
		ft_putstr(SDL_GetError());
		write(1, "\n", 1);
		free_data(data);
		exit(CREATE_RENDER);
	}
	SDL_FreeSurface(vis->surface);
	if ((vis->surface = IMG_Load("images/21_logo.png")) == NULL)
	{
		ft_putstr("SDL_CreateSurface error: ");
		ft_putstr(SDL_GetError());
		write(1, "\n", 1);
		free_data(data);
		exit(CREATE_SURFACE);
	}
	if ((vis->logo_21 = SDL_CreateTextureFromSurface(vis->rend, vis->surface)) == NULL)
	
	{
		ft_putstr("SDL_CreateRender error: ");
		ft_putstr(SDL_GetError());
		write(1, "\n", 1);
		free_data(data);
		exit(CREATE_RENDER);
	}
	SDL_FreeSurface(vis->surface);
	vis->run = true;
}