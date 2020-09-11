/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:58:16 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/11 21:48:30 by lmittie          ###   ########.fr       */
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
	return ants_number;
}

t_room_data		create_room(char *line)
{
	char		**splitted_line;
	t_room_data room_data;
	t_point		point;

	// TODO check_comment_func
	if ((splitted_line = ft_strsplit(line, ' ')) == NULL)
		exit(0);
	if (!splitted_line[0] || !splitted_line[1] || !splitted_line[2]
		|| !splitted_line[0][0] || !splitted_line[1][0]
		|| !splitted_line[2][0])
		exit(2);
	if (splitted_line[3])
		exit(2);
	if (((point.x = ft_atoi(splitted_line[1])) < 0)
		|| ((point.y = ft_atoi(splitted_line[2])) < 0))
		exit(2);
	if ((room_data.name = ft_strdup(splitted_line[0])) == NULL)
		exit(0);
	room_data.coords = point;
	// TODO write splitted_line delete function
	return room_data;
}

void 			create_room_list(t_room_list **list, t_room_data room_data)
{
	if (((*list) = malloc(sizeof(t_room_list))) == NULL)
		exit(0);
	(*list)->room_data = room_data;
	(*list)->next = NULL;
}

void 			push_back_room(t_room_list **list, t_room_data room_data, int *rooms_number)
{
	t_room_list *last;

	if (*list == NULL)
	{
		room_data.id = *rooms_number;
		create_room_list(list, room_data);
		(*rooms_number)++;
	}
	else
	{
		last = (*list);
		while (last->next)
			last = last->next;
		if (((last)->next = malloc(sizeof(t_room_list))) == NULL)
			exit(0);
		room_data.id = *rooms_number;
		(last)->next->room_data = room_data;
		(*rooms_number)++;
		(last)->next->next = NULL;
	}
}

void 			parse_rooms(t_data *data)
{
	char 	*line;

	while (get_next_line(0, &line) > 0)
	{
		push_back_room(&data->rooms, create_room(line), &data->rooms_number);
		ft_strdel(&line);
	}
}

void 	parse_map(t_data *data)
{
	data->ants_num = parse_ants_number();
	parse_rooms(data);
//	parse_links();
}
