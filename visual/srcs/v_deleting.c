/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_deleting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:54:10 by lmittie           #+#    #+#             */
/*   Updated: 2020/10/02 17:56:18 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		free_delete_exit(char **line, char **splitted_line, int exit_num)
{
	ft_strdel(line);
	ft_putnbr(exit_num);
	delete_splitted_line(&splitted_line);
	exit(exit_num);
}
