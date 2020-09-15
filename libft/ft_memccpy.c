/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:16:30 by lmittie           #+#    #+#             */
/*   Updated: 2019/09/09 20:16:51 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	ch;

	ch = (unsigned char)c;
	s = (unsigned char*)src;
	d = (unsigned char*)dst;
	while (n--)
	{
		*d++ = *s++;
		if (*(d - 1) == ch)
			return (d);
	}
	return (NULL);
}
