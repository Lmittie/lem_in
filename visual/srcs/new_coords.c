/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_coords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 19:29:33 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/25 19:14:59 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		new_coords(t_map_data *data, t_visual *vis)
{
	t_room_list	*room;

	room = data->rooms;
	vis->delta_x = (WIDTH - 400) / (data->max_coords.max_x - data->max_coords.min_x);
	vis->delta_y = (WIDTH - 400) / (data->max_coords.max_y - data->max_coords.min_y);
	while (room != NULL)
	{
		room->room_data->coords.x -= data->max_coords.min_x;
		room->room_data->coords.x *= vis->delta_x;
		room->room_data->coords.x += 200;

		room->room_data->coords.y -= data->max_coords.min_y;
		room->room_data->coords.y *= vis->delta_y;
		room->room_data->coords.y += 200;
		room = room->next;
	}
}