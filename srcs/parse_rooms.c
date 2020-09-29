/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:27:31 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/29 20:37:13 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room_data		*create_room(char **line, t_room_type room_type, t_data *data)
{
	char		**splitted_line;
	t_room_data	*room_data;
	t_point		point;

	if ((splitted_line = ft_strsplit(*line, ' ')) == NULL)
		exit(free_line_exit(line, data, MALLOC_ERROR));
	if (size_of_matrix_rows(splitted_line) != 3
		|| (((point.x = ft_atoi(splitted_line[1])) < 0)
			|| ((point.y = ft_atoi(splitted_line[2])) < 0)))
		exit(free_line_and_splitted_exit(line,
				&splitted_line, data, INVALID_ROOMS));
	if ((room_data = malloc(sizeof(t_room_data))) == NULL)
		exit(free_line_and_splitted_exit(line,
				&splitted_line, data, MALLOC_ERROR));
	if ((room_data->name = ft_strdup(splitted_line[0])) == NULL)
	{
		free(room_data);
		exit(free_line_and_splitted_exit(line,
				&splitted_line, data, MALLOC_ERROR));
	}
	room_data->coords = point;
	room_data->type = room_type;
	room_data->input_id = -1;
	room_data->output_id = -1;
	delete_splitted_line(&splitted_line);
	return (room_data);
}

int 		init_node(t_node **node, t_room_data *room_data)
{
	if (!(*node = malloc(sizeof(t_node))))
		return (0);
	(*node)->room = room_data;
	(*node)->next = NULL;
	return (1);
}

int			insert_room(t_node *(*hash_table)[HASH_TABLE_SIZE], t_room_data *room_data, int *id_counter)
{
	t_node	*node;
	t_node	*node_iter;
	int 	hash_value;

	if (room_data->type != START)
		room_data->input_id = (*id_counter)++;
	if (room_data->type != END)
		room_data->output_id = (*id_counter)++;
	if (!init_node(&node, room_data))
		return (0);
	hash_value = hasher(room_data->name);
	if ((*hash_table)[hash_value] == NULL)
		(*hash_table)[hash_value] = node;
	else
	{
		node_iter = (*hash_table)[hash_value];
		while (node_iter->next)
			node_iter = node_iter->next;
		node_iter->next = node;
	}
	return (1);
}

void			parse_rooms(t_data *data)
{
	char		*line;
	t_room_type room_type;

	room_type = DEFAULT;
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
			exit(free_line_exit(&line, data, INVALID_ROOMS));
		while (line[0] == '#')
		{
			room_type = check_if_comment(&line, data);
			if (room_type == PARSE_ERROR)
				exit(free_line_exit(&line, data, INVALID_ROOMS));
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
		if (!insert_room(&data->hash_table,
				create_room(&line, room_type, data),
				&data->id_counter))
			exit(free_line_exit(&line, data, MALLOC_ERROR));
		data->rooms_number++;
		room_type = DEFAULT;
		ft_strdel(&line);
	}
	// TODO check if links exists
}
