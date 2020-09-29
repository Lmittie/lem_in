/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_parse_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:22:39 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/29 19:10:41 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

t_paths		*create_struct(t_map_data *data)
{
	int		i;
	t_paths	*parse;
	t_paths	*root;
	t_paths *prev;

	i = 0;
	if (!(parse = malloc(sizeof(t_paths))))
		exit(MALLOC_ERROR);
	parse->ant_num = i + 1;
	parse->prev = NULL;
	if (!(parse->path = malloc(sizeof(int) * data->rooms_number)))
		exit(MALLOC_ERROR);
	ft_bnegative(parse->path, data->rooms_number);
	parse->path_root = parse->path;
	while (i != (data->ants_num - 1))
	{
		if (!(parse->next = malloc(sizeof(t_paths))))
			exit(MALLOC_ERROR);
		prev = parse;
		if (!(parse->next->path = malloc(sizeof(int) * data->rooms_number)))
			exit(MALLOC_ERROR);
		ft_bnegative(parse->next->path, data->rooms_number);
		parse->next->path_root = parse->next->path;
		parse = parse->next;
		parse->prev = prev;
		parse->ant_num = i + 2;
		parse->next = NULL;
		i++;
	}
	while (parse->prev != NULL)
		parse = parse->prev;
	return (parse);
}

int			return_id_by_name(t_room_list *rooms, char *name_room)
{
	t_room_list *cur;

	cur = rooms;
	while (ft_strcmp(cur->room_data->name, name_room))
		cur = cur->next;
	return(cur->room_data->id);
}

void		work_with_split_line(t_room_list *rooms, char **splitted_line, t_paths *paths)
{
	int		i;
	char	**ant_room_name;
	int		number_curr_ant;
	int		room_id;
	t_paths	*root;

	i = 0;
	root = paths;
	while (splitted_line[i])
	{
		if (!(ant_room_name = ft_strsplit(splitted_line[i], '-')))
		{
			delete_splitted_line(splitted_line);
			exit (MALLOC_ERROR);
		}
		number_curr_ant = ft_atoi((ant_room_name[0] + 1));
		while (paths->ant_num != number_curr_ant)
			paths = paths->next;
		room_id = return_id_by_name(rooms, ant_room_name[1]);
		(*paths->path) = room_id;
		paths->path++;

		i++;
		paths = root;
	}
}

void		fill_path(t_map_data *data, t_paths *paths)
{
	char *line;
	char **splitted_line;

	while (get_next_line(0, &line) > 0)
	{
		if ((splitted_line = ft_strsplit(line, ' ')) == NULL)
		{
			ft_strdel(&line);
			exit(MALLOC_ERROR);
		}
		work_with_split_line(data->rooms, splitted_line, paths);
		delete_splitted_line(splitted_line);
	}
}

void		parse_path(t_map_data *data, t_visual *vis)
{
	int i;

	vis->paths = create_struct(data);
	fill_path(data, vis->paths);
	while (vis->paths != NULL)
	{
		i = 0;
		vis->paths->path = vis->paths->path_root;
		printf ("ant_num = %d\n####################\npath_id = ", vis->paths->ant_num);
		while (vis->paths->path[i] >= 0)
		{
			printf ("%d ", vis->paths->path[i]);
			i++;
		}
		printf ("\n####################\n");
		vis->paths = vis->paths->next;
	}
}