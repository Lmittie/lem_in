/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 16:50:50 by lmittie           #+#    #+#             */
/*   Updated: 2019/09/12 16:50:52 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_isalpha(char *str)
{
	if (ft_strlen(str) == 0)
		return (0);
	while (*str)
	{
		if (!(ft_isalpha(*str)))
			return (0);
		str++;
	}
	return (1);
}
