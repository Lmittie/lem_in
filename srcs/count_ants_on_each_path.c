/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_ants_on_each_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:08:01 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/25 21:26:03 by lmittie          ###   ########.fr       */
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
//		printf("ants num: %d, path len = %d\n", path_iter->path_data->ants, path_iter->path_data->length);
		if (!(path_iter->path_data->ants_by_id =
				malloc(sizeof(int) * path_iter->path_data->ants)))
			exit(MALLOC_ERROR);
		path_iter->path_data->last_ant_id = 0;
		prev_iter = path_iter;
		path_iter = path_iter->next;
	}
}

int		count_ants_on_each_path(t_paths **paths, int ants_num)
{
	int			ants_on_path;
	t_paths		*path;
	t_paths		*next_path;
	int			counter;

	counter = 0;
	ants_on_path = 0;
	path = (*paths);
	next_path = (*paths)->next;
	while (ants_on_path < ants_num)
	{
		if ((*paths)->next == NULL)
		{
			path->ants_num = ants_num;
			counter = path->path_len + ants_num;
			break ;
		}
		else if (path->path_len + path->ants_num
				<= next_path->path_len + next_path->ants_num)
		{
			// in case both paths have prev paths
			if (path->prev && next_path->prev)
			{
				path = path->prev;
				next_path = next_path->prev;
				continue ;
			// in case we compare first and last paths
			} else if (next_path->prev == NULL)
			{
				path = *paths;
				next_path = path->next;
				continue ;
			}
			// in case first path is begining of list
			path->ants_num++;
			if ((path->path_len - 1) + (path->ants_num - 1) > counter)
				counter = (path->path_len - 1) + (path->ants_num - 1);
		}
		else
		{
			next_path->ants_num++;
			if ((next_path->path_len - 1) + (next_path->ants_num - 1) > counter)
				counter = next_path->path_len + next_path->ants_num;
			if (next_path->next == NULL)
			{
				next_path = *paths;
				path = path->next;
			} else if (path->next == NULL)
			{
				next_path = next_path->next;
				path = *paths;
			} else
			{
				path = path->next;
				next_path = next_path->next;
			}
		}
		ants_on_path++;
	}
	return (counter);
}