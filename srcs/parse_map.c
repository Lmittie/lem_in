/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:58:16 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/14 21:14:44 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 			parse_ants_number()
{
	char	*line;
	int		ants_number;

	if (get_next_line(0, &line) <= 0)
		exit(1);
	if ((ants_number = ft_atoi(line)) <= 0)
	{
		ft_strdel(&line);
		exit(1);
	}
	ft_strdel(&line);
	return (ants_number);
}

int 			size_of_matrix_rows(char **matrix)
{
	int counter;

	counter = 0;
	while (matrix[counter] != NULL)
	{
		if (!matrix[counter][0])
			return (10);
		counter++;
	}
	return (counter);
}

t_room_data		create_room(char *line, t_room_type room_type)
{
	char		**splitted_line;
	t_room_data room_data;
	t_point		point;

	if ((splitted_line = ft_strsplit(line, ' ')) == NULL)
		exit(10);
	if (size_of_matrix_rows(splitted_line) != 3
		|| (((point.x = ft_atoi(splitted_line[1])) < 0)
		|| ((point.y = ft_atoi(splitted_line[2])) < 0)))
	{
		delete_splitted_line(splitted_line);
		exit(2);
	}
	if ((room_data.name = ft_strdup(splitted_line[0])) == NULL)
	{
		delete_splitted_line(splitted_line);
		exit(10);
	}
	room_data.coords = point;
	room_data.type = room_type;
	delete_splitted_line(splitted_line);
	return (room_data);
}

int 			return_room_index(char *room_name, t_room_list *list)
{
	t_room_list *head;

	head = list;
	while (head)
	{
		printf("name in list = %s, name from params = %s\n", head->room_data.name, room_name);
		if (!ft_strcmp(head->room_data.name, room_name))
			return (head->room_data.id);
		head = head->next;
	}
	return (-1);
}

void 			init_matrix(int ***adjacency_matrix, int size)
{
	int i;

	i = -1;
	if ((*adjacency_matrix = malloc(sizeof(int*) * size)) == NULL)
		exit(10);
	while (++i < size)
	{
		if (((*adjacency_matrix)[i] = malloc(sizeof(int) * size)) == NULL)
			exit(10);
		ft_bzero((*adjacency_matrix)[i], sizeof(int) * size);
	}
}

void 			fill_adjacency_matrix(int index1, int index2, int ***adjacency_matrix, int size)
{
	if (*adjacency_matrix == NULL)
		init_matrix(adjacency_matrix, size);
	(*adjacency_matrix)[index1][index2] = 1;
	(*adjacency_matrix)[index2][index1] = 1;
}

// TODO free line
void 			add_link(char *line, t_data *data)
{
	char		**splitted_line;
	int 		index1;
	int 		index2;

	if ((splitted_line = ft_strsplit(line, '-')) == NULL)
		exit(10);
	if (size_of_matrix_rows(splitted_line) != 2)
	{
		delete_splitted_line(splitted_line);
		exit(3);
	}
	if ((index1 = return_room_index(splitted_line[0], data->rooms)) == -1
		|| (index2 = return_room_index(splitted_line[1], data->rooms)) == -1)
	{
		delete_splitted_line(splitted_line);
		exit(3);
	}
	fill_adjacency_matrix(index1, index2, &data->adjacency_matrix, data->rooms_number);
}

t_room_type		check_if_comment(char **line, t_data *data)
{
	t_room_type type;

	type = DEFAULT;
	if (!ft_strncmp(*line, "#", 1))
	{
		if (!ft_strcmp(*line, "##start"))
		{
			type = (data->start == -1) ? START : PARSE_ERROR;
		}
		if (!ft_strcmp(*line, "##end"))
		{
			type = (data->end == -1) ? END : PARSE_ERROR;
		}
		get_next_line(0, line);
	}
	return type;
}

void 			parse_rooms(t_data *data)
{
	char 	*line;
	t_room_type room_type;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
			exit(6);
		if (ft_strchr(line, '-') != NULL)
		{
			add_link(line, data);
			break ;
		}
		if ((room_type = check_if_comment(&line, data)) == PARSE_ERROR)
		{
			ft_strdel(&line);
			exit(5);
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

void 		parse_links(t_data *data)
{
	char 	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
			exit(6);
		if (check_if_comment(&line, data) == PARSE_ERROR)
		{
			ft_strdel(&line);
			exit(5);
		}
		add_link(line, data);
		ft_strdel(&line);
	}
}

void 	parse_map(t_data *data)
{
	data->ants_num = parse_ants_number();
	parse_rooms(data);
	parse_links(data);
}
