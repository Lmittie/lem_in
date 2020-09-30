/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:54:10 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/30 20:32:54 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_hash_table(t_node *(*hash_table)[HASH_TABLE_SIZE])
{
	int		i;
	t_node	*tmp_node;
	t_node 	*node;

	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		if ((*hash_table)[i] != NULL)
		{
			node = (*hash_table)[i];
			while (node)
			{
				tmp_node = node;
				node = node->next;
				ft_strdel(&tmp_node->room->name);
				free(tmp_node->room);
				tmp_node->next = NULL;
				free(tmp_node);
			}
		}
		i++;
	}
}

void		free_path(t_path **path)
{
	t_path	*tmp_id;

	while (*path != NULL)
	{
		tmp_id = *path;
		*path = (*path)->next;
		free(tmp_id);
		tmp_id = NULL;
	}
}

void		free_paths(t_paths **paths)
{
	t_paths *tmp_path;

	while ((*paths) != NULL)
	{
		tmp_path = *paths;
		(*paths) = (*paths)->next;
		free_path(&tmp_path->id_list);
		if (tmp_path->ants_by_id)
			free(tmp_path->ants_by_id);
		free(tmp_path);
		tmp_path = NULL;
	}
}

void		free_matrix(int ***matrix, int size)
{
	int i;

	if (*matrix == NULL)
		return;
	i = 0;
	while (i < size)
	{
		if ((*matrix)[i])
			free((*matrix)[i]);
		(*matrix)[i] = NULL;
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

void		free_data(t_data *data)
{
	int i;

	if (data->direction_id)
		free(data->direction_id);
	if (data->rooms_by_id)
	{
		i = 0;
		while (i < data->rooms_number)
		{
			if (data->rooms_by_id[i])
				ft_strdel(&data->rooms_by_id[i]);
			i++;
		}
		free(data->rooms_by_id);
	}
	free_hash_table(&data->hash_table);
	free_paths(&data->paths);
	free_matrix(&data->adjacency_matrix, data->id_counter);
}

void		delete_splitted_line(char ***splitted_line)
{
	int i;

	i = 0;
	while ((*splitted_line)[i])
	{
		free((*splitted_line)[i]);
		(*splitted_line)[i] = NULL;
		i++;
	}
	free(*splitted_line);
	splitted_line = NULL;
}

t_exit_code	free_line_and_splitted_exit(char **line, char ***splitted_line, t_data *data, t_exit_code exit_code)
{
	ft_strdel(line);
	delete_splitted_line(splitted_line);
	free_data(data);
	write(2, "ERROR\n", 6);
	return (exit_code);
}

t_exit_code	free_line_exit(char **line, t_data *data, t_exit_code exit_code)
{
	ft_strdel(line);
	free_data(data);
	write(2, "ERROR\n", 6);
	return (exit_code);
}

t_exit_code	free_data_exit(t_data *data, t_exit_code exit_code)
{
	free_data(data);
	if (exit_code != 0)
		write(2, "ERROR\n", 6);
	return (exit_code);
}

t_exit_code	no_free_exit(t_exit_code exit_code)
{
	write(2, "ERROR\n", 6);
	return (exit_code);
}
