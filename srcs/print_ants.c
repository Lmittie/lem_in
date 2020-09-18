/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:30:03 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/18 21:23:15 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void 	add_new_ant(t_path_data **path_data, int ***ants, int last_ant_id)
{
	(*ants)[last_ant_id] = (*path_data)->path; // now ant is in the start room
	// add id to ants_id for current path
	(*path_data)->
			ants_by_id[(*path_data)->last_ant_id++] = last_ant_id;
	(*path_data)->ants--;
}

void 	move_ants_in_current_path(t_path_data **path_data, int ***ants, int *ants_at_end)
{
	int i;
	int *ptr;

	i = 0;
	while (i < (*path_data)->last_ant_id)
	{
		if (*((*ants)[(*path_data)->ants_by_id[i]]) <= (*path_data)->length)
		{
			if (*((*ants)[(*path_data)->ants_by_id[i]]) == (*path_data)->length)
				(*ants_at_end)++;
			else
			{
				ptr = (*ants)[(*path_data)->ants_by_id[i]];
				(*ants)[(*path_data)->ants_by_id[i]]++;
			}
		}
		i++;
	}
}

void 	print_current_movements(int **ants, int last_ant_id, char **rooms_by_id, int end_id)
{
	int j;

	j = 0;
	while (j < last_ant_id)
	{
//		if (*(ants[j]) == end_id)
//		{
//			j++;
//			continue;
//		}
		ft_putchar('L');
		ft_putnbr(j + 1);
		ft_putchar('-');
		ft_putstr(rooms_by_id[*(ants[j])]);
		ft_putchar(' ');
		j++;
	}
	ft_putchar('\n');
}

void	print_ants(t_data *data)
{
	int			ants_at_end;
	int 		last_ant_id;
	t_path_list	*list_iter;
	int 		**ants;

	ants_at_end = 0;
	last_ant_id = 0;
	if (!(ants = malloc(sizeof(int*) * data->ants_num)))
		exit(MALLOC_ERROR);
	while (ants_at_end < data->ants_num)
	{
		list_iter = data->paths;
		while (list_iter)
		{
			// add new ant on the root if ants at the start are existed yet
			if (list_iter->path_data->ants)
				add_new_ant(&list_iter->path_data, &ants, last_ant_id++);
			// move rest of ants on the path
			move_ants_in_current_path(&list_iter->path_data, &ants, &ants_at_end);
			list_iter = list_iter->next;
		}
		//printing current movements
		print_current_movements(ants, last_ant_id, data->rooms_by_id, data->end);
	}
}