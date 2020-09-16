/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:37:30 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/16 14:52:31 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void 			add_link(char *line, t_data *data)
{
	char		**splitted_line;
	int 		index1;
	int 		index2;

	if ((splitted_line = ft_strsplit(line, '-')) == NULL)
	{
		free_line(&line);
		exit(10);
	}
	if (size_of_matrix_rows(splitted_line) != 2)
		free_delete_exit(&line, splitted_line, 3);
	if ((index1 = return_room_index(splitted_line[0], data->rooms)) == -1
		|| (index2 = return_room_index(splitted_line[1], data->rooms)) == -1)
		free_delete_exit(&line, splitted_line, 3);
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
