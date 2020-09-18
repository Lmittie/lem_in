/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:08:37 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/18 19:46:30 by acarlett         ###   ########.fr       */
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
	int ii = 100;
	int	f_i = 0;
	int jj = 30; 
	int	f_j = 0; 
	int	kk = 100;
	int	f_k = 0;

	//TODO привести все в порядок под структуру!!!
	//TODO сделать обработку клавиы escape для выхода
	
	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type ==SDL_QUIT)
				run = 0;
		}
		
		ii = flow_color(30, 100, &f_i, ii);
		jj = flow_color(30, 80, &f_j, jj);
		kk = flow_color(100, 140, &f_k, kk);
		SDL_SetRenderDrawColor(rend, ii, jj, kk, 255);
		SDL_RenderClear(rend);
		
		draw_random_points(20000, true, rend);

		SDL_RenderPresent(rend);
	}


	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
