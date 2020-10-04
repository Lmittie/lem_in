/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_parse_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:22:39 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/04 20:55:33 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		image_load(t_visual *vis, t_paths **parse, t_map_data *data, int i)
{
	char	*line;
	int		tmp;
	char	a[6];

	tmp = i % 10;
	if (!tmp)
		tmp = 1;
	a[0] = tmp + 48;
	a[1] = '.';
	a[2] = 'p';
	a[3] = 'n';
	a[4] = 'g';
	a[5] = '\0';
	line = ft_strjoin("images/ant\0", a);
	if (((*parse)->surface = IMG_Load(line)) == NULL)
	{
		ft_putstr(SDL_GetError());
		write(1, "\n", 1);
		exit(CREATE_SURFACE);
	}
	if (((*parse)->tex = SDL_CreateTextureFromSurface(vis->rend,
											(*parse)->surface)) == NULL)
	{
		ft_putstr(SDL_GetError());
		write(1, "\n", 1);
		exit(CREATE_TEXTURE);
	}
	ft_strdel(&line);
	SDL_FreeSurface((*parse)->surface);
}

t_paths		*create_struct(t_map_data *data, t_visual *vis)
{
	int		i;
	t_paths	*parse;
	t_paths	*root;
	t_paths *prev;

	i = 0;
	if (!(parse = ft_memalloc(sizeof(t_paths))))
		exit(MALLOC_ERROR);
	image_load(vis, &parse, data, i + 1);
	parse->ant_num = i + 1;
	parse->start = 1;
	parse->prev = NULL;
	if (!(parse->id_list = ft_memalloc(sizeof(int) * data->rooms_number)))
		exit(MALLOC_ERROR);
	ft_bnegative(parse->id_list, data->rooms_number);
	parse->id_list_root = parse->id_list;
	while (i != (data->ants_num - 1))
	{
		if (!(parse->next = ft_memalloc(sizeof(t_paths))))
			exit(MALLOC_ERROR);
		prev = parse;
		if (!(parse->next->id_list = ft_memalloc(sizeof(int) *
									data->rooms_number)))
			exit(MALLOC_ERROR);
		ft_bnegative(parse->next->id_list, data->rooms_number);
		parse->next->id_list_root = parse->next->id_list;
		parse = parse->next;
		parse->prev = prev;
		parse->start = 1;
		parse->ant_num = i + 2;
		parse->next = NULL;
		i++;
		image_load(vis, &parse, data, i + 1);
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
	return (cur->room_data->id);
}

void		work_with_split_line(t_room_list *rooms,
							char **splitted_line, t_paths *paths)
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
			delete_splitted_line(&splitted_line);
			exit(MALLOC_ERROR);
		}
		number_curr_ant = ft_atoi((ant_room_name[0] + 1));
		while (paths->ant_num != number_curr_ant)
			paths = paths->next;
		room_id = return_id_by_name(rooms, ant_room_name[1]);
		(*paths->id_list) = room_id;
		paths->id_list++;
		i++;
		paths = root;
		delete_splitted_line(&ant_room_name);
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
		delete_splitted_line(&splitted_line);
		ft_strdel(&line);
	}
}

void		parse_path(t_map_data *data, t_visual *vis)
{
	int i;

	vis->paths = create_struct(data, vis);
	fill_path(data, vis->paths);
	while (vis->paths->next != NULL)
	{
		vis->paths->id_list = vis->paths->id_list_root;
		vis->paths = vis->paths->next;
		if (vis->paths->next == NULL)
			vis->paths->id_list = vis->paths->id_list_root;
	}
	while (vis->paths->prev != NULL)
		vis->paths = vis->paths->prev;
}
