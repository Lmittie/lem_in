/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_algorithm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:53:20 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/28 20:14:32 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	init_algo_params(t_dinic_data *dinic_data, t_data *data)
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

static int	bfs(t_dinic_data *data, int **capacity_matrix)
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
		to = -1;
		while (++to < data->n)
		{
			if (data->distance[to] == -1
				&& (data->flow_matrix[v][to] < capacity_matrix[v][to]))
			{
				data->queue[qt++] = to;
				data->distance[to] = data->distance[v] + 1;
			}
		}
	}
	return (data->distance[data->end] != -1);
}

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	dfs(int v, int flow, t_dinic_data *data, int **capacity_matrix)
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

t_paths		*dinic(t_data *data)
{
	int				max_flow;
	int				pushed;
	t_paths			*best_paths;
	t_dinic_data	dinic_data;

	init_algo_params(&dinic_data, data);
	best_paths = NULL;
	max_flow = 0;
	while (bfs(&dinic_data, data->adjacency_matrix) && ++max_flow)
	{
		ft_bzero(dinic_data.ptr, sizeof(int) * data->id_counter);
		while ((pushed = dfs(dinic_data.start,
						INF,
						&dinic_data,
						data->adjacency_matrix)))
		{
			max_flow += pushed;
			find_best_path(&best_paths,
						&dinic_data,
						data->ants_num,
						data->direction_id);
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
