/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:40:02 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/25 14:56:27 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

int		main()
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	Uint32			render_flags;
	SDL_Event		event;
	SDL_Surface		*surface;
	SDL_Texture		*tex;
	bool			run;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		ft_putstr("SDL initialization error:");
		ft_putstr(SDL_GetError());
		exit(INIT_SDL_ERROR);
	}
	IMG_Init(IMG_INIT_PNG);
	win = SDL_CreateWindow("LEM IN VISUAL",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							WIDTH,
							HEIGHT,
							SDL_WINDOW_SHOWN);
	render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	rend = SDL_CreateRenderer(win, -1, render_flags);
	surface = SDL_LoadBMP("images/dog.bmp");
	tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	SDL_RenderClear(rend);
	run = true;
	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type ==SDL_QUIT)
				run = false;
			if (event.type ==SDL_KEYUP)
				run = false;
		}
		SDL_RenderCopy(rend, tex, NULL, NULL);
		SDL_SetRenderDrawColor(rend, 39, 0, 68, 255);
		SDL_RenderPresent(rend);
	}
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}