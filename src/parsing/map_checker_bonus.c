/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:47:23 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 10:47:30 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "ft_printf.h"
#include "libft.h"
#include "map.h"

static int	is_playable(t_map *map)
{
	size_t	current_y;
	size_t	current_x;
	char	tile;

	current_y = 0;
	while (current_y < map->size_y)
	{
		current_x = 0;
		while (current_x < map->size_x)
		{
			tile = get_tile(map, current_x, current_y);
			if (tile == '0' || tile == 'N' || tile == 'S'
				|| tile == 'E' || tile == 'W' || tile == 'D')
			{
				if (get_tile(map, current_x + 1, current_y) == ' '
					|| get_tile(map, current_x, current_y + 1) == ' '
					|| get_tile(map, current_x - 1, current_y) == ' '
					|| get_tile(map, current_x, current_y - 1) == ' ')
					return (0);
			}
			current_x++;
		}
		current_y++;
	}
	return (1);
}

int	check_map_character(t_map *map)
{
	const char	allowed_character[] = "01 NSEWD";
	size_t		current_x;
	size_t		current_y;

	current_y = 0;
	while (current_y < map->size_y)
	{
		current_x = 0;
		while (current_x < map->size_x)
		{
			if (!ft_strchr(allowed_character, map->grid[current_y][current_x]))
				return (1);
			current_x++;
		}
		current_y++;
	}
	return (0);
}

/**
 * @brief Return a boolean if the map is valid and playable
 *
 * @param map 
 * @return 1 if not and 0 if yes
 */
int	is_valid_map(t_map *map)
{
	if (!is_playable(map))
	{
		ft_dprintf(2, "Error\nMap is not playable\n");
		return (1);
	}
	if (check_map_character(map))
	{
		ft_dprintf(2, "Error\nMap contain invalid character\n");
		return (1);
	}
	return (0);
}
