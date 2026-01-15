/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_verif.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:39:42 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 16:02:38 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stddef.h>
#include <stdio.h>

static int	is_valid_color(char *color)
{
	size_t	i;
	int		val;
	int		as_overflow;

	if (ft_strchr(color, ',') && ft_strchr(color, ',') - color < 1)
		return (0);
	i = 0;
	while (color[i])
	{
		if (color[i] == ',' || color[i] == '\n')
			break ;
		else if (!ft_isdigit(color[i]))
			return (0);
		i++;
	}
	val = ft_atoi(color, &as_overflow);
	if (val > 255 || val < 0 || as_overflow)
		return (0);
	return (1);
}

/**
 * @brief Return a boolean that say if the color code is rga ok
 *
 * @param color 
 * @return 1 if ok / 0 else
 */
int	is_valid_rgb(char *color)
{
	int	i;

	if (ft_isdigit(color[1]) || color[1] == '+' || color[1] == '-')
	{
		if (!is_valid_color(color + 1))
			return (0);
	}
	else
		return (0);
	i = 0;
	while (ft_strchr(color, ','))
	{
		color = ft_strchr(color, ',');
		if (color++ == NULL || !*color)
			return (0);
		if (ft_isdigit(color[0]) || color[0] == '+' || color[0] == '-')
		{
			if (!is_valid_color(color))
				return (0);
		}
		else
			return (0);
		i++;
	}
	return (i == 2);
}
