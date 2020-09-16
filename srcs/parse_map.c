/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:58:16 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/15 18:38:52 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void 	parse_map(t_data *data)
{
	data->ants_num = parse_ants_number();
	parse_rooms(data);
	if (data->start == -1 || data->end == -1)
		exit(INVALID_ROOMS);
	parse_links(data);
}
