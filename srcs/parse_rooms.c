/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:27:31 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/23 19:40:41 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room_data		*create_room(char *line, t_room_type room_type)
{
	char		**splitted_line;
	t_room_data	*room_data;
	t_point		point;

	if ((splitted_line = ft_strsplit(line, ' ')) == NULL)
	{
		ft_strdel(&line);
		exit(MALLOC_ERROR);
	}
	if (size_of_matrix_rows(splitted_line) != 3
		|| (((point.x = ft_atoi(splitted_line[1])) < 0)
			|| ((point.y = ft_atoi(splitted_line[2])) < 0)))
	{
		free_delete_exit(&line, splitted_line, INVALID_ROOMS);
	}
	if ((room_data = malloc(sizeof(t_room_data))) == NULL)
		free_delete_exit(&line, splitted_line, MALLOC_ERROR);
	if ((room_data->name = ft_strdup(splitted_line[0])) == NULL)
		free_delete_exit(&line, splitted_line, MALLOC_ERROR);
	room_data->coords = point;
	room_data->type = room_type;
	room_data->input_id = -1;
	room_data->output_id = -1;
	delete_splitted_line(splitted_line);
	return (room_data);
}

void			parse_rooms(t_data *data)
{
	char		*line;
	t_room_type room_type;

	room_type = DEFAULT;
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
		{
			ft_strdel(&line);
			exit(INVALID_ROOMS);
		}
		while (!ft_strncmp(line, "#", 1))
		{
			room_type = check_if_comment(&line, data);
			if (room_type == PARSE_ERROR) {
				ft_strdel(&line);
				exit(INVALID_ROOMS);
			}
			if (room_type == START)
				data->start = data->id_counter;
			if (room_type == END)
				data->end = data->id_counter;
		}
		if (ft_strchr(line, '-') != NULL)
		{
			add_link(line, data);
			break ;
		}
		push_back_room(&data->rooms, create_room(line, room_type), &data->id_counter);
		data->rooms_number++;
		room_type = DEFAULT;
		ft_strdel(&line);
	}
	// TODO check if links exists
}
