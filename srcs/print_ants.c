/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:30:03 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/27 17:38:29 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void 	add_new_ant(t_paths **path, t_path ***ants, int last_ant_id)
{
	(*ants)[last_ant_id] = (*path)->id_list; // now ant is in the start room
	// add id to ants_id for current path
	(*path)->ants_by_id[(*path)->last_ant_id++] = last_ant_id;
	(*path)->ants_num--;
}

void 	move_ants_in_current_path(t_paths **path, t_path ***ants, int *ants_at_end, int end)
{
	int i;

	i = 0;
	while (i < (*path)->last_ant_id)
	{
		// if ant isnt in the end room
		if ((*ants)[(*path)->ants_by_id[i]] != NULL &&
			(*ants)[(*path)->ants_by_id[i]]->id != end)
		{
			// move ant in the next room
			(*ants)[(*path)->ants_by_id[i]] = (*ants)[(*path)->ants_by_id[i]]->next;
			// if its the end room then increment number of ants at the end
			if (((*ants)[(*path)->ants_by_id[i]])->id == end)
				(*ants_at_end)++;
		} else
		{
			// else dont count the ants which are already at the end while printing
			(*ants)[(*path)->ants_by_id[i]] = NULL;
		}
		i++;
	}
}

void 	print_current_movements(t_path **ants, int last_ant_id, char **rooms_by_id)
{
	int j;

	j = 0;
	while (j < last_ant_id)
	{
		if (ants[j] == NULL)
		{
			j++;
			continue;
		}
		ft_putchar('L');
		ft_putnbr(j + 1);
		ft_putchar('-');
		ft_putstr(rooms_by_id[ants[j]->id]);
		if (j + 1 != last_ant_id)
			ft_putchar(' ');
		j++;
	}
	ft_putchar('\n');
}

void 	init_ants(t_paths **paths)
{
	t_paths *path_iter;

	path_iter = (*paths);
	while (path_iter)
	{
		if (!(path_iter->ants_by_id = malloc(sizeof(int) * path_iter->ants_num)))
			exit(MALLOC_ERROR);
		path_iter = path_iter->next;
	}
}

void	print_ants(t_data *data)
{
	int			ants_at_end;
	int 		last_ant_id;
	t_paths		*list_iter;
	t_path 		**ants;

	ants_at_end = 0;
	last_ant_id = 0;
	if (!(ants = malloc(sizeof(t_path *) * data->ants_num)))
		exit(MALLOC_ERROR);
	init_ants(&data->paths);
	while (ants_at_end < data->ants_num)
	{
		list_iter = data->paths;
		while (list_iter)
		{
			// add new ant on the root if ants at the start are existed yet
			if (list_iter->ants_num > 0)
				add_new_ant(&list_iter, &ants, last_ant_id++);
			// move rest of ants on the path
			move_ants_in_current_path(&list_iter, &ants, &ants_at_end, data->direction_id[data->end]);
			list_iter = list_iter->next;
		}
		//printing current movements
		print_current_movements(ants, last_ant_id, data->rooms_by_id);
	}
}