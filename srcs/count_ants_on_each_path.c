/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_ants_on_each_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:08:01 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/27 18:13:51 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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