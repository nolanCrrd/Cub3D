/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_empty_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:05:45 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 11:05:50 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "get_next_line.h"

/**
 * @brief Skip all the line int he fd that contain only whitespaces
 *
 * @param fd
 * @return 
 */
char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && is_blank(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
