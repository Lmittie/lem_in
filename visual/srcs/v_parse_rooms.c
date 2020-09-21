/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:27:31 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/21 18:58:26 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

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
		free_delete_exit(&line, splitted_line, INVALID_ROOMS);
	if ((room_data = malloc(sizeof(t_room_data))) == NULL)
		free_delete_exit(&line, splitted_line, MALLOC_ERROR);
	if ((room_data->name = ft_strdup(splitted_line[0])) == NULL)
		free_delete_exit(&line, splitted_line, MALLOC_ERROR);
	room_data->coords = point;
	room_data->type = room_type;
	delete_splitted_line(splitted_line);
	return (room_data);
}

void			parse_rooms(t_map_data *data)
{
	char		*line;
	t_room_type room_type;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
		{
			ft_strdel(&line);
			exit(INVALID_ROOMS);
		}
		if (ft_strchr(line, '-') != NULL)
		{
			add_link(line, data);
			break ;
		}
		if ((room_type = check_if_comment(&line, data)) == PARSE_ERROR)
		{
			ft_strdel(&line);
			exit(INVALID_ROOMS);
		}
		push_back_room(&data->rooms, create_room(line, room_type), &data->rooms_number);
		if (room_type == START)
			data->start = data->rooms_number - 1;
		if (room_type == END)
			data->end = data->rooms_number - 1;
		ft_strdel(&line);
	}
	// TODO check if links exists
}
