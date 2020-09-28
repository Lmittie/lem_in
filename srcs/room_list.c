/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:56:33 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/23 19:40:41 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room_data	*return_room(char *room_name, t_room_list *list)
{
	t_room_list *head;

	head = list;
	while (head)
	{
		if (!ft_strcmp(head->room_data->name, room_name))
			return (head->room_data);
		head = head->next;
	}
	return (NULL);
}

static void	create_room_list(t_room_list **list, t_room_data *room_data)
{
	if (((*list) = malloc(sizeof(t_room_list))) == NULL)
		exit(MALLOC_ERROR);
	(*list)->room_data = room_data;
	(*list)->next = NULL;
}

void		push_back_room(t_room_list **list, t_room_data *room_data,
							int *id_counter)
{
	t_room_list *last;

	if (room_data->type != START)
		room_data->input_id = (*id_counter)++;
	if (room_data->type != END)
		room_data->output_id = (*id_counter)++;
	if (*list == NULL)
		create_room_list(list, room_data);
	else
	{
		last = (*list);
		while (last->next)
			last = last->next;
		if (((last)->next = malloc(sizeof(t_room_list))) == NULL)
			exit(MALLOC_ERROR);
		(last)->next->room_data = room_data;
		(last)->next->next = NULL;
	}
}
