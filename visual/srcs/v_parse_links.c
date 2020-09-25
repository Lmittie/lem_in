/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_parse_links.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:37:30 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/25 15:15:58 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void	add_link(char *line, t_map_data *data)
{
	char	**splitted_line;
	int		index1;
	int		index2;

	if ((splitted_line = ft_strsplit(line, '-')) == NULL)
	{
		ft_strdel(&line);
		exit(MALLOC_ERROR);
	}
	if (size_of_matrix_rows(splitted_line) != 2)
		free_delete_exit(&line, splitted_line, INVALID_LINKS);
	index1 = return_room_index(splitted_line[0], data->rooms);
	index2 = return_room_index(splitted_line[1], data->rooms);
	if ((index1 == -1) || (index2 == -1))
		free_delete_exit(&line, splitted_line, INVALID_LINKS);
}

void	parse_links(t_map_data *data)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '\0')
			exit(INVALID_LINKS);
		if (check_if_comment(&line, data) == PARSE_ERROR)
		{
			ft_strdel(&line);
			exit(INVALID_LINKS);
		}
		add_link(line, data);
		ft_strdel(&line);
	}
}
