/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:37:30 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/15 18:37:30 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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
