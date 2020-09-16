/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:32:19 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/16 21:12:42 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void		first_init_param(t_visual **v_data)
{
	(*v_data)->mlx = mlx_init();
	(*v_data)->win = mlx_new_window((*v_data)->mlx, WIN_X, WIN_Y, "lem_in");
	(*v_data)->img = mlx_new_image((*v_data)->mlx, WIN_X, WIN_Y);
	(*v_data)->data = (int *)mlx_get_data_addr(
		(*v_data)->img,
		&((*v_data)->undef1),
		&((*v_data)->undef2),
		&((*v_data)->undef3)
	);
}

int			key_press(int key, void *a)
{
	//
}

void		make_visual(t_data data)
{
	t_visual *v_data;

	if (!(v_data = malloc(sizeof(t_visual))))
		exit(MALLOC_ERROR);
	first_init_param(&v_data);
	mlx_hook(v_data->win, 2, 0, key_press, (void *)v_data);
	mlx_loop(v_data->mlx);
}
