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
	t_map_data data;

	init_structure(&data);
	parse_map(&data);
	printf("rooms_number = %d\n", data.rooms_number);
	while (data.rooms != NULL)
	{
		printf("NAME = %s	ID = %d		X_CORD = %d		Y_CORD = %d\n",
					data.rooms->room_data->name,
					data.rooms->room_data->id,
					data.rooms->room_data->coords.x,
					data.rooms->room_data->coords.y);
		data.rooms = data.rooms->next;		
	}
	return (0);
}
