/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:39:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/27 20:45:36 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_structure(t_data *data)
{
	(data)->ants_num = -1;
	(data)->adjacency_matrix = NULL;
	(data)->rooms = NULL;
	(data)->rooms_number = 0;
	(data)->id_counter = 0;
	(data)->start = -1;
	(data)->end = -1;
	(data)->rooms_by_id = NULL;
	(data)->direction_id = NULL;
	(data)->paths = NULL;
}

int		main(void)
{
	t_data data;

	init_structure(&data);
	parse_map(&data);
	printf("rooms number: %d\n", data.rooms_number);
	if (!(data.paths = dinic(&data)))
		exit(PARSE_ERROR);
	print_ants(&data);
	return (0);
}

