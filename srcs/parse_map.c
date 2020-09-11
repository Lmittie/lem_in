/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:58:16 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/11 18:12:47 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 	parse_ants_number()
{
	char	*line;
	long	ants_number;

	if (get_next_line(0, &line) <= 0)
		exit(-1);

}

void 	parse_map(t_data *data)
{
	parse_ants_number();
	parse_rooms();
	parse_links();
}
