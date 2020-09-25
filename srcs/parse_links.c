/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:37:30 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/23 19:40:41 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_link(char *line, t_data *data)
{
	char			**splitted_line;
	t_room_data		*room1;
	t_room_data		*room2;

	if ((splitted_line = ft_strsplit(line, '-')) == NULL)
	{
		ft_strdel(&line);
		exit(MALLOC_ERROR);
	}
	if (size_of_matrix_rows(splitted_line) != 2)
		free_delete_exit(&line, splitted_line, INVALID_LINKS);
	room1 = return_room(splitted_line[0], data->rooms);
	room2 = return_room(splitted_line[1], data->rooms);
	if ((room1 == NULL) || (room2 == NULL))
		free_delete_exit(&line, splitted_line, INVALID_LINKS);
	fill_adjacency_matrix(room1, room2, &(data->adjacency_matrix), data->id_counter);
}

void	parse_links(t_data *data)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
			exit(INVALID_LINKS);
		while (line && !ft_strncmp(line, "#", 1))
		{
			if (check_if_comment(&line, data) == PARSE_ERROR)
			{
				ft_strdel(&line);
				exit(INVALID_ROOMS);
			}
			if (!line)
				return ;
		}
			add_link(line, data);
			ft_strdel(&line);
	}
}
