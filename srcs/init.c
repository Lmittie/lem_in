/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:05:02 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/28 19:05:02 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_structure(t_data *data)
{
	(data)->ants_num = -1;
	(data)->adjacency_matrix = NULL;
	(data)->rooms = NULL;
	(data)->rooms_number = 0;
	(data)->id_counter = 0;
	(data)->start = -1;
	(data)->end = -1;
	(data)->rooms_by_id = NULL;
	(data)->direction_id = NULL;
	(data)->paths = NULL;
}
