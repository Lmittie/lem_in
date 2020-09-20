/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 21:41:07 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/20 16:35:51 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "../SDL/include/SDL.h"
# include "../SDL/include/SDL_image.h"
# include <stdbool.h>
# include <time.h>
# include "../../libft/libft.h"

# define WIDTH	1000
# define HEIGHT	1000

typedef enum	e_exit_code
{
				INIT_ERROR = 1
}				t_error_code;

/*
* random.c
*/
int		random_number(int nbr_min, int nbr_max);
int		random_color();
void	draw_random_points(int nbr_points, bool randomize_color, SDL_Renderer *rend);

/*
* flow_color.c
*/
int		flow_color(int low, int high, int *flag, int myself);


#endif