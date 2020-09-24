// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 16:08:37 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/21 16:20:37 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void	init_structure(t_map_data *data)
{
	(data)->ants_num = -1;
	(data)->adjacency_matrix = NULL;
	(data)->rooms_number = 0;
	(data)->start = -1;
	(data)->end = -1;
}

int		main()
{
	t_map_data	data;
	t_visual	vis;

	init_structure(&data);
	parse_map(&data);
	check_coords(&data);
	new_coords(&data, &vis); //TODO Минимальная и максимальная координата по X и Y должны стоять на границах
							// рисуемой зоны (200, 800)px
	
	printf("rooms_number = %d\n", data.rooms_number);
	printf ("delta_x = %d		delta_y = %d\n", vis.delta_x, vis.delta_y);
	while (data.rooms != NULL)
	{
		printf("NAME = %s	ID = %d		X_CORD = %d		Y_CORD = %d\n",
					data.rooms->room_data->name,
					data.rooms->room_data->id,
					data.rooms->room_data->coords.x,
					data.rooms->room_data->coords.y);
		data.rooms = data.rooms->next;		
	}
	printf ("X = (max, min) = (%d; %d)		Y = (max, min) = (%d; %d)\n",
					data.max_coords.max_x,
					data.max_coords.min_x,
					data.max_coords.max_y,
					data.max_coords.min_y);
	return (0);
}

/* 800 - 200 = 600 px -> Область для рисования
**
** 600 / (max_x(~42) - min_x(4)) = 38 ячеек каждая по 15 px
**
** ((all_coords - min_x) * 15(px)) + 200
*/

