/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 18:59:03 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/04 20:43:53 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		handle_room_type(t_map_data *data, t_room_type room_type,
char *line, int exit_code)
{
	if (room_type == PARSE_ERROR)
		free_strdel_exit(1, data, line, INVALID_ROOMS);
	if (room_type == START)
		data->start = data->rooms_number;
	if (room_type == END)
		data->end = data->rooms_number;
}

void		free_strdel_exit(int str_out, t_map_data *data,
char *line, int exit_code)
{
	if (str_out == 1)
		ft_putstr("Empty line\n");
	if (str_out == 2)
		ft_putstr("too much start- or end- rooms\n");
	if (str_out == 3)
		ft_putstr("Parse Error\n");
	free_data(data);
	ft_strdel(&line);
	exit(exit_code);
}

void		get_error_free_data(t_map_data *data, int exit_code, int str_out)
{
	if (str_out == 1)
		ft_putstr("SDL_CreateRender error: ");
	if (str_out == 2)
		ft_putstr("SDL_CreateSurface error: ");
	ft_putstr(SDL_GetError());
	write(1, "\n", 1);
	free_data(data);
	exit(str_out);
}
