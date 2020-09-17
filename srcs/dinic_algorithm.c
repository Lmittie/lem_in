/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_algorithm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:53:20 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/17 19:54:05 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

#define INF 1000000000

void	init_algo_params(t_dinic_data *dinic_data, t_data *data)
{
	int i;

	dinic_data->start = data->start;
	dinic_data->end = data->end;
	dinic_data->n = data->rooms_number;
	init_matrix(&dinic_data->capacity_matrix, dinic_data->n);
	if (!(dinic_data->room_entry = malloc(sizeof(int) * dinic_data->n)))
		exit(10);
	i = 0;
	while (i < dinic_data->n)
		dinic_data->room_entry[i++] = 1;
	dinic_data->room_entry[dinic_data->start] = -1;
	dinic_data->room_entry[dinic_data->end] = -1;
	if (!(dinic_data->queue = malloc(sizeof(int) * dinic_data->n)))
		exit(10);
	if (!(dinic_data->ptr = malloc(sizeof(int) * dinic_data->n)))
		exit(10);
	if (!(dinic_data->distance = malloc(sizeof(int) * dinic_data->n)))
		exit(10);
	copy(dinic_data->capacity_matrix,
			data->adjacency_matrix,
			dinic_data->n);
}

int		bfs(t_dinic_data *data)
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
	while (qh < qt)
	{
		v = data->queue[qh++];
		to = 0;
		while (to < data->n)
		{
			if (data->distance[to] == -1 && data->capacity_matrix[v][to]
				&& data->room_entry[to])
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

void 	add_room_to_path(t_path_data *path_data, int room_id, int len)
{
	if (path_data->path == NULL)
	{
		if (!(path_data->path = malloc(sizeof(int) * (len + 1))))
			exit(MALLOC_ERROR);
		ft_bzero(path_data->path, sizeof(int) * (len + 1));
	}
	path_data->path[len] = room_id;
}

int		dfs(int v, int flow, t_dinic_data *data, t_path_data *path_data)
{
	int pushed;

	if (!flow || v == data->end)
		return ((!flow) ? 0 : flow);
	while (data->ptr[v] < data->n)
	{
		if (data->distance[data->ptr[v]] != data->distance[v] + 1
		|| !data->capacity_matrix[v][data->ptr[v]]
		|| !data->room_entry[data->ptr[v]])
		{
			++data->ptr[v];
			continue ;
		}
		pushed = dfs(data->ptr[v],
					min(flow, data->capacity_matrix[v][data->ptr[v]]),
					data, path_data);
		if (pushed)
		{
			add_room_to_path(path_data, data->ptr[v], data->distance[data->ptr[v]]);
			data->room_entry[data->ptr[v]]--;
			data->capacity_matrix[v][data->ptr[v]] -= pushed;
			data->capacity_matrix[data->ptr[v]][v] += pushed;
			return (pushed);
		}
		++data->ptr[v];
	}
	return (0);
}

void 	push_back_path(t_path_list **paths_list, t_path_data path_data)
{
	t_path_list *last;

	if ((*paths_list) == NULL)
	{
		if (!(*paths_list = malloc(sizeof(t_path_list))))
			exit(MALLOC_ERROR);
		if (!((*paths_list)->path_data = malloc(sizeof(t_path_data))))
			exit(MALLOC_ERROR);
		(*paths_list)->path_data = &path_data;
		(*paths_list)->next = NULL;
	} else
	{
		last = (*paths_list);
		while (last->next)
			last = last->next;
		if (((last)->next = malloc(sizeof(t_path_list))) == NULL)
			exit(MALLOC_ERROR);
		(last)->next->path_data = &path_data;
		(last)->next->next = NULL;
	}
}

int		dinic(t_data *data)
{
	int				max_flow;
	int				pushed;
	t_dinic_data	dinic_data;
	t_path_data		path_data;

	init_algo_params(&dinic_data, data);
	max_flow = 0;
	while (bfs(&dinic_data))
	{
		ft_bzero(dinic_data.ptr, sizeof(int) * data->rooms_number);
		ft_bzero(&path_data, sizeof(t_path_data));
		while ((pushed = dfs(dinic_data.start, INF, &dinic_data, &path_data)))
		{
			max_flow += pushed;
			push_back_path(&data->paths, path_data);
			path_data.path = NULL;
		}
	}
	printf("max flow = %d\n", max_flow);
	return (max_flow);
}
