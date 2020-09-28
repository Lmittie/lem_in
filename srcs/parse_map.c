/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:58:16 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/24 16:04:24 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	fill_rooms_by_id(char ***rooms, t_room_list *room_list, int n)
{
	int				i;
	t_room_list		*list_iter;

	if (!(*rooms = malloc(sizeof(char*) * n)))
		exit(MALLOC_ERROR);
	i = -1;
	list_iter = room_list;
	while (++i < n)
	{
		if (!((*rooms)[i] = ft_strdup(list_iter->room_data->name)))
			exit(MALLOC_ERROR);
		list_iter->room_data->id = i;
		list_iter = list_iter->next;
	}
}

void	fill_direction_id(int **direction_id, t_room_list *room_list, int n)
{
	int				i;
	t_room_list		*list_iter;

	if (!(*direction_id = malloc(sizeof(int) * n)))
		exit(MALLOC_ERROR);
	i = -1;
	list_iter = room_list;
	while (++i < n)
	{
		(*direction_id)[i] = list_iter->room_data->id;
		if (list_iter->room_data->type == START
				|| list_iter->room_data->type == END
				|| list_iter->room_data->output_id == i)
			list_iter = list_iter->next;
	}
}

void	parse_map(t_data *data)
{
	data->ants_num = parse_ants_number();
	parse_rooms(data);
	fill_rooms_by_id(&data->rooms_by_id, data->rooms, data->rooms_number);
	fill_direction_id(&data->direction_id, data->rooms, data->id_counter);
	if (data->start == -1 || data->end == -1)
		exit(INVALID_ROOMS);
	parse_links(data);
}
