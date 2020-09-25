/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:28:33 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/24 18:28:30 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	copy(int **dst, int **src, int size)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	if (dst == NULL || src == NULL || *(dst) == NULL || *(src) == NULL)
		return ;
	while (i != size)
	{
		while (j != size)
		{
			dst[i][j] = src[i][j];
			j++;
		}
		i++;
		j = 0;
	}
}

void	init_matrix(int ***adjacency_matrix, int size)
{
	int i;

	i = -1;
	if ((*adjacency_matrix = malloc(sizeof(int*) * size)) == NULL)
		exit(10);
	while (++i < size)
	{
		if (((*adjacency_matrix)[i] = malloc(sizeof(int) * size)) == NULL)
			exit(10);
		ft_bzero((*adjacency_matrix)[i], sizeof(int) * size);
	}
}

void	fill_adjacency_matrix(t_room_data *room1, t_room_data *room2, int ***adjacency_matrix, int size)
{
	if (*adjacency_matrix == NULL)
		init_matrix(adjacency_matrix, size);

	if (room1->type != END && room2->type != START)
		(*adjacency_matrix)[room1->output_id][room2->input_id] = 1;
	if (room2->type != END && room1->type != START)
		(*adjacency_matrix)[room2->output_id][room1->input_id] = 1;

	if (room1->type != START && room1->type != END)
		(*adjacency_matrix)[room1->input_id][room1->output_id] = 1;
	if (room2->type != START && room2->type != END)
		(*adjacency_matrix)[room2->input_id][room2->output_id] = 1;
}
