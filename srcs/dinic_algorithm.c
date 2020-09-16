/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinic_algorithm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:53:20 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/16 16:34:19 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

#define INF 1000000000

void 	init_algo_params(t_dinic_data *dinic_data, t_data data)
{
	dinic_data->n = data.rooms_number;
	init_matrix(&dinic_data->capacity_matrix, dinic_data->n);
	if (!(dinic_data->queue = malloc(sizeof(int) * dinic_data->n)))
		exit(10);
	if (!(dinic_data->ptr = malloc(sizeof(int) * dinic_data->n)))
		exit(10);
	if (!(dinic_data->distance = malloc(sizeof(int) * dinic_data->n)))
		exit(10);
	new_memcpy(
			dinic_data->capacity_matrix,
			data.adjacency_matrix,
			dinic_data->n
	);
	dinic_data->start = data.start;
	dinic_data->end = data.end;
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
			if (data->distance[to] == -1 && data->capacity_matrix[v][to])
			{
				data->queue[qt++] = to;
				data->distance[to] = data->distance[v] + 1;
			}
			to++;
		}
	}
	return (data->distance[data->end] != -1);
}

int 	min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int		dfs(int v, int flow, t_dinic_data *data, t_data *ddata)
{
	int pushed;

	if (!flow || v == data->end)
		return ((!flow) ? 0 : flow);
	while (data->ptr[v] < data->n)
	{
		if (data->distance[data->ptr[v]] != data->distance[v] + 1
		|| !data->capacity_matrix[v][data->ptr[v]])
		{
			++data->ptr[v];
			continue;
		}
		pushed = dfs(data->ptr[v], min(flow, data->capacity_matrix[v][data->ptr[v]]), data, ddata);
		if (pushed)
		{
			data->capacity_matrix[v][data->ptr[v]] -= pushed;
			data->capacity_matrix[data->ptr[v]][v] += pushed;
			return (pushed);
		}
		++data->ptr[v];
	}
	return (0);
}

int		dinic(t_data data)
{
	int				max_flow;
	int				pushed;
	t_dinic_data	dinic_data;

	init_algo_params(&dinic_data, data);
	max_flow = 0;
	while(bfs(&dinic_data))
	{
		ft_bzero(dinic_data.ptr, sizeof(int) * data.rooms_number);
		while ((pushed = dfs(dinic_data.start, INF, &dinic_data, &data)))
			max_flow += pushed;
	}
	printf("max flow = %d\n", max_flow);
	return (max_flow);
}