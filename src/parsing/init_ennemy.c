/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ennemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:39:28 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 16:53:57 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ennemy.h"
#include "ft_printf.h"
#include "map.h"
#include "parsing.h"

/**
 * @brief init the player position based on the map value
 *
 * @param map filled map to look in
 * @param player player where fill data
 * @return 0 if success / 1 if error
 */
static int	init_start_position(t_map *map, t_ennemy *ennemy)
{
	size_t	cr_x;
	size_t	cr_y;

	cr_y = 0;
	while (cr_y < map->size_y)
	{
		cr_x = 0;
		while (cr_x < map->size_x)
		{
			if (map->grid[cr_y][cr_x] == 'M')
			{
				if (ennemy->pos[X] != -1)
				{
					ft_dprintf(2, "Error\nMultiple ennemy start position\n");
					return (1);
				}
				ennemy->pos[X] = cr_x + 0.5;
				ennemy->pos[Y] = cr_y + 0.5;
			}
			cr_x++;
		}
		cr_y++;
	}
	return (ennemy->pos[X] == -1);
}

/**
 * @brief Init all the player information
 *
 * @param map reference map
 * @param player player where fill data
 * @return 0 if succes / 1 if error
 */
int	init_ennemy(t_map *map, t_ennemy *ennemy)
{
	ennemy->pos[X] = -1;
	ennemy->pos[Y] = -1;
	if (init_start_position(map, ennemy))
	{
		if (ennemy->pos[X] == -1)
			ft_dprintf(2, "Error\nNo ennmey starting position\n");
		return (1);
	}
	return (0);
}
