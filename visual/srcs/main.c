/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:08:37 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/20 19:50:29 by acarlett         ###   ########.fr       */
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
		exit(INIT_ERROR);
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

	//TODO привести все в порядок под структуру!!!
	//TODO сделать обработку клавишы escape для выхода

	
	tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	SDL_RenderClear(rend);
	run = true;

	int ii = 100;
	int	f_i = 0;
	int jj = 30; 
	int	f_j = 0; 
	int	kk = 100;
	int	f_k = 0;
	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type ==SDL_QUIT)
				run = false;
		}
		

	SDL_RenderCopy(rend, tex, NULL, NULL);
		// ii = flow_color(30, 100, &f_i, ii);
		// jj = flow_color(30, 80, &f_j, jj);
		// kk = flow_color(100, 140, &f_k, kk);
		// SDL_SetRenderDrawColor(rend, ii, jj, kk, 255);

		draw_random_points(200000, true, rend);

		SDL_RenderPresent(rend);
	}


	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
