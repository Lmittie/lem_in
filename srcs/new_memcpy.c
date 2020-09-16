/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_memcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:24:39 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/16 16:35:38 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		new_memcpy(int **dst, int **src, int size)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	if (dst == NULL || src == NULL || *(dst) == NULL || *(src) == NULL)
		exit(123);
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