/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_ants_on_each_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:08:01 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/18 19:20:17 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void 	delete_path(t_path_list **data)
{
	free((*data)->path_data->path);
	(*data)->path_data->path = NULL;
	free((*data)->path_data);
	(*data)->path_data = NULL;
	free(*data);
	*data = NULL;
}

void 	delete_useless_paths(t_path_list **paths)
{
	t_path_list *path_iter;
	t_path_list *prev_iter;

	path_iter = *paths;
	prev_iter = NULL;
	while (path_iter)
	{
		if (!path_iter->path_data->ants)
		{
			if (prev_iter == NULL)
			{
				(*paths) = (*paths)->next;
				delete_path(&path_iter);
				path_iter = (*paths);
				continue ;
			} else
			{
				prev_iter->next = prev_iter->next->next;
				delete_path(&path_iter);
				path_iter = prev_iter->next;
				continue ;
			}
		}
		if (!(path_iter->path_data->ants_by_id =
				malloc(sizeof(int) * path_iter->path_data->ants)))
			exit(MALLOC_ERROR);
		path_iter->path_data->last_ant_id = 0;
		prev_iter = path_iter;
		path_iter = path_iter->next;
	}
}

void	count_ants_on_each_path(t_data *data)
{
	int			ants_at_end;
	t_path_list *path_iter;

	ants_at_end = 0;
	while (ants_at_end < data->ants_num)
	{
		path_iter = data->paths;
		while (path_iter)
		{
			if (path_iter->path_data->dist_from_end)
				path_iter->path_data->dist_from_end--;
			if (!path_iter->path_data->dist_from_end)
			{
				path_iter->path_data->ants++;
				if (++ants_at_end >= data->ants_num)
					break ;
			}
			path_iter = path_iter->next;
		}
	}
	delete_useless_paths(&data->paths);
}