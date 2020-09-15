/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:39:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/15 21:43:22 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"
#include <stdio.h>

void init_structure(t_data *data) {
	(data)->ants_num = -1;
	(data)->adjacency_matrix = NULL;
	(data)->rooms = NULL;
	(data)->rooms_number = 0;
	(data)->start = -1;
	(data)->end = -1;
}

void 	print_rooms_info(t_data data);

int 	main()
{
	t_data data;

	init_structure(&data);
	parse_map(&data);
	dinic(data);

	print_rooms_info(data);
	return (0);
}

void 	print_rooms_info(t_data data)
{
	printf("rooms number: %d\n", data.rooms_number);
	while (data.rooms != NULL)
	{
		printf("room name: %s, room id: %lu, room coords: %d, %d, ",
			   data.rooms->room_data->name,
			   data.rooms->room_data->id,
			   data.rooms->room_data->coords.x, data.rooms->room_data->coords.y);

		if (data.rooms->room_data->type == START)
			printf("room type: START\n");
		else if (data.rooms->room_data->type == END)
			printf("room type: END\n");
		else printf("room type: DEFAULT\n");

		data.rooms = data.rooms->next;
	}

	printf("matrix:\n");
	printf("   ");
	for (int i = 0; i < data.rooms_number; ++i) {
		printf("%d ", i);
	}
	printf(":\n");

	for (int i = 0; i < data.rooms_number; ++i) {
		printf("%d: ", i);
		for (int j = 0; j < data.rooms_number; ++j)
			printf("%d ", data.adjacency_matrix[i][j]);
		printf("\n");
	}
}