/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 19:35:05 by acarlett          #+#    #+#             */
/*   Updated: 2020/09/18 19:43:23 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

int		flow_color(int low, int high, int *flag, int myself)
{
	int i;

	i = myself;
	if(i != low && !(*flag))
	{
		i--;
		if (i == low)
			(*flag) = 1;
	
	}
	else if(i != high && (*flag))
	{
		i++;
		if (i == high)
			(*flag) = 0;
	
	}
	return (i);
}