/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:56:33 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/14 17:56:33 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void 			create_room_list(t_room_list **list, t_room_data *room_data)
{
	if (((*list) = malloc(sizeof(t_room_list))) == NULL)
		exit(0);
	(*list)->room_data = room_data;
	(*list)->next = NULL;
}

void 			push_back_room(t_room_list **list, t_room_data *room_data, int *rooms_number)
{
	t_room_list *last;

	if (*list == NULL)
	{
		room_data->id = *rooms_number;
		create_room_list(list, room_data);
		(*rooms_number)++;
	}
	else
	{
		last = (*list);
		while (last->next)
			last = last->next;
		if (((last)->next = malloc(sizeof(t_room_list))) == NULL)
			exit(0);
		room_data->id = *rooms_number;
		(last)->next->room_data = room_data;
		(*rooms_number)++;
		(last)->next->next = NULL;
	}
}
