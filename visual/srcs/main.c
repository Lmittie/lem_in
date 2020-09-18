/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:08:37 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/18 19:19:11 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

int		main()
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	int				run;
	SDL_Event		event;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		ft_putstr("SDL initialization error:");
		ft_putstr(SDL_GetError());
		exit(INIT_ERROR);
	}
	win = SDL_CreateWindow("LEM IN VISUAL",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							WIDTH,
							HEIGHT,
							SDL_WINDOW_SHOWN);
	
	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	run = 1;
	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type ==SDL_QUIT)
				run = 0;
		}

		SDL_SetRenderDrawColor(rend, 40, 40, 40, 255);
		SDL_RenderClear(rend);
		
		SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
		draw_random_points(500, false, rend);

		SDL_RenderPresent(rend);
	}


	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
