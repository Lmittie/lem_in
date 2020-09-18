/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 18:59:03 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/18 19:18:58 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

int		random_number(int nbr_min, int nbr_max)
{
	return (rand() % (nbr_max + nbr_min));
}

int		random_color()
{
	return (random_number(0, 255));
}

void	draw_random_points(int nbr_points, bool randomize_color, SDL_Renderer *rend)
{
	int i;

	i = 0;
	while (i < nbr_points)
	{
		if (randomize_color)
			SDL_SetRenderDrawColor(rend,
									random_color(),
									random_color(),
									random_color(),
									255);
		SDL_RenderDrawPoint(rend, random_number(0, WIDTH), random_number(0, HEIGHT));
		i++;
	}
}