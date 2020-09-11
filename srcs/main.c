/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:39:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/11 18:03:33 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"


void init_structure(t_data **data) {
	*data = malloc(sizeof(t_data*));
	(*data)->ants_num = -1;
	(*data)->adjacency_matrix = NULL;
	(*data)->rooms = NULL;
}

int 	main()
{
	t_data *data;

	init_structure(&data);
	parse_map(data);
	return (0);
}