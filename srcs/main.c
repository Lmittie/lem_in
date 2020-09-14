/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:39:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/14 21:39:52 by lmittie          ###   ########.fr       */
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

int 	main()
{
	t_data data;

	init_structure(&data);
	parse_map(&data);
	 printf("rooms number: %d\n", data.rooms_number);
	 while (data.rooms != NULL)
	 {
	 	printf("room name: %s, room id: %d, room coords: %d, %d\n",
		  data.rooms->room_data->name, data.rooms->room_data->id, data.rooms->room_data->coords.x, data.rooms->room_data->coords.y);
	 	data.rooms = data.rooms->next;
	 }
	 printf("matrix:\n");
	 for (int i = 0; i < data.rooms_number; ++i) {
	 	for (int j = 0; j < data.rooms_number; ++j)
	 		printf("%d ", data.adjacency_matrix[i][j]);
	 	printf("\n");
	 }
	return (0);
}