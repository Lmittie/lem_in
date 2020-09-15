/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:04:12 by lmittie           #+#    #+#             */
/*   Updated: 2019/09/12 15:17:23 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_back(t_list **alst, void const *cont, size_t cont_size)
{
	t_list *blst;

	blst = *alst;
	while (blst->next)
		blst = (blst)->next;
	(blst)->next = ft_lstnew(cont, cont_size);
}
