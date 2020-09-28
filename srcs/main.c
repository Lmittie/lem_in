/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:39:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/28 19:06:46 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_data data;

	init_structure(&data);
	parse_map(&data);
	printf("rooms number: %d\n", data.rooms_number);
	if (!(data.paths = dinic(&data)))
		exit(PARSE_ERROR);
	print_ants(&data);
	return (0);
}
