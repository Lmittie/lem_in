/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:32:19 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/16 21:37:45 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void		init_param(t_visual **v_data)
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
// int		blackground(t_visual *v_data)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (j != WIN_Y)
// 	{
// 		v_data->x0 = 0;
// 		v_data->y0 = j;
// 		v_data->x_end = WIN_X;
// 		v_data->y_end = j;
// 		make_line(v_data, 0x303030);
// 		j++;
// 	}
// 	return (0);
// }

int			key_press(int key, void *a)
{
	t_visual *v_data;

	v_data = (t_visual *)a;
	if (key == 53)
		exit(0);
	// blackground();
	return (0);
}

void		make_visual(t_data data)
{
	t_visual *v_data;

	if (!(v_data = malloc(sizeof(t_visual))))
		exit(MALLOC_ERROR);
	init_param(&v_data);
	v_data->data[(int)(((float)WIN_Y / 2.0) *
		WIN_X + ((float)WIN_X / 2.0))] = 0xff0000;
	mlx_put_image_to_window(
		v_data->mlx,
		v_data->win,
		v_data->img,
		0, 0
	);
	mlx_hook(v_data->win, 2, 0, key_press, (void *)v_data);
	mlx_loop(v_data->mlx);
}
