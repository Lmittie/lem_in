/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:54:10 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/17 18:56:15 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		delete_splitted_line(char **splitted_line)
{
	int		i;

	i = 0;
	while (splitted_line[i])
	{
		free(splitted_line[i]);
		splitted_line[i] = NULL;
		i++;
	}
	free(splitted_line);
	splitted_line = NULL;
}

void		free_delete_exit(char **line, char **splitted_line, int exit_num)
{
	printf("hereee\n");
	ft_strdel(line);
	delete_splitted_line(splitted_line);
	exit(exit_num);
}
