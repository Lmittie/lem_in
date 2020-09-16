/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:22:52 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/16 17:46:52 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		parse_ants_number(void)
{
	char	*line;
	int		ants_number;

	if (get_next_line(0, &line) <= 0)
		exit(INVALID_ANTS);
	if ((ants_number = ft_atoi(line)) <= 0)
	{
		ft_strdel(&line);
		exit(INVALID_ANTS);
	}
	ft_strdel(&line);
	return (ants_number);
}
