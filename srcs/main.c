/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:39:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/29 19:04:26 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 	hasher(const char *name)
{
	int hash;

	hash = 53;
	while (*name)
	{
		hash = hash * 33 + hash + (int)(*name);
		name++;
	}
	if (hash < 0)
		hash *= -1;
	hash %= HASH_TABLE_SIZE;
	return (hash);
}

int		main(void)
{
	t_data data;

	init_structure(&data);
	parse_map(&data);
	printf("rooms number: %d\n", data.rooms_number);
	if (!(data.paths = dinic(&data)))
		exit(free_data_exit(&data, INVALID_ROOMS));
	print_ants(&data);
	return (free_data_exit(&data, 0));
}
