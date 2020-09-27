/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_algorithm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:53:20 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/27 20:34:01 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

#define INF 1000000000

void	init_algo_params(t_dinic_data *dinic_data, t_data *data)
{
	dinic_data->start = data->start;
	dinic_data->end = data->end;
	dinic_data->n = data->id_counter;
	if (!(dinic_data->queue = malloc(sizeof(int) * dinic_data->n)))
		exit(MALLOC_ERROR);
	if (!(dinic_data->ptr = malloc(sizeof(int) * dinic_data->n)))
		exit(MALLOC_ERROR);
	if (!(dinic_data->distance = malloc(sizeof(int) * dinic_data->n)))
		exit(MALLOC_ERROR);
	init_matrix(&dinic_data->flow_matrix, dinic_data->n);
}

int		bfs(t_dinic_data *data, int **capacity_matrix)
{
	int qh;
	int qt;
	int v;
	int to;

	qh = 0;
	qt = 0;
	data->queue[qt++] = data->start;
	ft_memset(data->distance, -1, sizeof(int) * data->n);
	data->distance[data->start] = 0;
	while (qh < qt && data->distance[data->end] == -1)
	{
		v = data->queue[qh++];
		to = 0;
		while (to < data->n)
		{
			if (data->distance[to] == -1
				&& (data->flow_matrix[v][to] < capacity_matrix[v][to]))
			{
				data->queue[qt++] = to;
				data->distance[to] = data->distance[v] + 1;
			}
			to++;
		}
	}
	return (data->distance[data->end] != -1);
}

int		min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int		dfs(int v, int flow, t_dinic_data *data, int **capacity_matrix)
{
	int pushed;

	if (!flow || v == data->end)
		return ((!flow) ? 0 : flow);
	while (data->ptr[v] < data->n)
	{
		if (data->distance[data->ptr[v]] != data->distance[v] + 1
		|| !(capacity_matrix[v][data->ptr[v]]
			- data->flow_matrix[v][data->ptr[v]]))
		{
			++data->ptr[v];
			continue ;
		}
		pushed = dfs(data->ptr[v],
					min(flow, capacity_matrix[v][data->ptr[v]]
					- data->flow_matrix[v][data->ptr[v]]), data, capacity_matrix);
		if (pushed)
		{
			data->flow_matrix[v][data->ptr[v]] += pushed;
			data->flow_matrix[data->ptr[v]][v] -= pushed;
			return (pushed);
		}
		++data->ptr[v];
	}
	return (0);
}

void 	add_room_to_path(t_path **path, int room_id, int *dir_id, int *length)
{
	t_path *path_iter;

	if ((*path) == NULL)
	{
		if (!((*path) = malloc(sizeof(t_path))))
			exit(MALLOC_ERROR);
		(*path)->id = dir_id[room_id];
		(*path)->next = NULL;
		(*length)++;
		return ;
	}
	path_iter = (*path);
	while (path_iter->next)
		path_iter = path_iter->next;
	if (path_iter->id != dir_id[room_id])
	{
		if (!(path_iter->next = malloc(sizeof(t_path))))
			exit(MALLOC_ERROR);
		path_iter->next->id = dir_id[room_id];
		path_iter->next->next = NULL;
		(*length)++;
	}
}

void 	push_back_path(t_paths *path_before, t_path *path, int path_length)
{
	t_paths *path_to_add;

	if (!(path_to_add = malloc(sizeof(t_paths))))
		exit(MALLOC_ERROR);
	path_to_add->id_list = path;
	path_to_add->path_len = path_length;
	path_to_add->ants_num = 0;
	path_to_add->ants_by_id = NULL;
	path_to_add->last_ant_id = 0;
	path_to_add->next = NULL;
	path_to_add->prev = path_before;
	path_before->next = path_to_add;
}

void 	push_front_path(t_paths **head, t_path *path, int path_length)
{
	t_paths *path_to_add;

	if (!(path_to_add = malloc(sizeof(t_paths))))
		exit(MALLOC_ERROR);
	path_to_add->id_list = path;
	path_to_add->path_len = path_length;
	path_to_add->ants_num = 0;
	path_to_add->ants_by_id = NULL;
	path_to_add->last_ant_id = 0;
	path_to_add->prev = NULL;
	path_to_add->next = *head;
	(*head)->prev = path_to_add;
	*head = path_to_add;
}

void 	insert_before_path(t_paths *path_after, t_path *path, int path_length)
{
	t_paths *path_to_add;

	if (!(path_to_add = malloc(sizeof(t_paths))))
		exit(MALLOC_ERROR);
	path_to_add->id_list = path;
	path_to_add->path_len = path_length;
	path_to_add->ants_num = 0;
	path_to_add->ants_by_id = NULL;
	path_to_add->last_ant_id = 0;
	path_to_add->next = path_after;
	path_to_add->prev = path_after->prev;
	path_after->prev->next = path_to_add;
	path_after->prev = path_to_add;
}

void 	add_path(t_paths **paths, t_path *path, int path_length)
{
	t_paths *path_iter;
	t_paths *prev_iter;

	if (*paths == NULL)
	{
		if (!(*paths = malloc(sizeof(t_paths))))
			exit(MALLOC_ERROR);
		(*paths)->id_list = path;
		(*paths)->ants_num = 0;
		(*paths)->path_len = path_length;
		(*paths)->ants_by_id = NULL;
		(*paths)->last_ant_id = 0;
		(*paths)->next = NULL;
		(*paths)->prev = NULL;
		return ;
	}
	path_iter = (*paths);
	while (path_iter && path_length > path_iter->path_len)
	{
		prev_iter = path_iter;
		path_iter = path_iter->next;
	}
	if (path_iter == NULL)
		push_back_path(prev_iter, path, path_length);
	else if (path_iter == (*paths))
		push_front_path(paths, path, path_length);
	else
		insert_before_path(path_iter, path, path_length);
}

void 	pathfinding(int v, t_dinic_data *data, t_paths **paths, int *dir_id)
{
	int				to;
	static int 		path_length = 0;
	static t_path	*path = NULL;

	if (v == data->end)
	{
		add_room_to_path(&path, v, dir_id, &path_length);
		add_path(paths, path, path_length);
		path = NULL;
		path_length = 0;
		return ;
	}
	to = 0;
	while (to < data->n)
	{
		if (data->flow_matrix[v][to] == 1)
		{
			add_room_to_path(&path, v, dir_id, &path_length);
			pathfinding(to, data, paths, dir_id);
			if (v != data->start)
				return ;
		}
		to++;
	}
}

void 	find_best_path(t_paths **best_paths, t_dinic_data *data, int ants_num, int *dir_id)
{
	t_paths *current_paths;
	int 	output_lines;

	// bfs for current paths
	current_paths = NULL;
	pathfinding(data->start, data, &current_paths, dir_id);
	// check lines count -> if it more - dont add new path, return old
	output_lines = count_ants_on_each_path(&current_paths, ants_num);
	current_paths->output_lines = output_lines;
	if ((*best_paths == NULL) || (output_lines < (*best_paths)->output_lines))
		*best_paths = current_paths;
}

t_paths		*dinic(t_data *data)
{
	// delete
	int				max_flow;
	int				pushed;
	// not delete
	t_paths 		*best_paths;
	t_dinic_data	dinic_data;

	init_algo_params(&dinic_data, data);
	best_paths = NULL;
	max_flow = 0;
	while (bfs(&dinic_data, data->adjacency_matrix) && ++max_flow)
	{
		ft_bzero(dinic_data.ptr, sizeof(int) * data->id_counter);
		while ((pushed = dfs(dinic_data.start, INF, &dinic_data, data->adjacency_matrix)))
		{
			max_flow += pushed;
			find_best_path(&best_paths, &dinic_data, data->ants_num, data->direction_id);
		}
	}
	printf("max flow = %d\n", max_flow);
	t_paths *iter = best_paths;
	int count = 0;
	while (iter)
	{
		count++;
		iter = iter->next;
	}
	printf("count = %d\n", count);
	return (best_paths);
}
