/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:28:33 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/16 17:46:52 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

void	fill_adjacency_matrix(int index1, int index2, int ***adjacency_matrix, int size)
{
	if (*adjacency_matrix == NULL)
		init_matrix(adjacency_matrix, size);
	(*adjacency_matrix)[index1][index2] = 1;
	(*adjacency_matrix)[index2][index1] = 1;
}
