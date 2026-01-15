/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:39:33 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 10:39:49 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_printf.h"
#include "map.h"
#include "player.h"
#include <math.h>

/**
 * @brief init the player position based on the map value
 *
 * @param map filled map to look in
 * @param player player where fill data
 * @return 0 if success / 1 if error
 */
static int	init_start_position(t_map *map, t_player *player)
{
	size_t	cr_x;
	size_t	cr_y;

	cr_y = 0;
	while (cr_y < map->size_y)
	{
		cr_x = 0;
		while (cr_x < map->size_x)
		{
			if (map->grid[cr_y][cr_x] == 'N' || map->grid[cr_y][cr_x] == 'S'
				|| map->grid[cr_y][cr_x] == 'E' || map->grid[cr_y][cr_x] == 'W')
			{
				if (player->pos[X] != -1)
				{
					ft_dprintf(2, "Error\nMultiple start position\n");
					return (1);
				}
				player->pos[X] = cr_x + 0.5;
				player->pos[Y] = cr_y + 0.5;
			}
			cr_x++;
		}
		cr_y++;
	}
	return (player->pos[X] == -1);
}

/**
 * @brief Init the player direction angle and vector
 *
 * @param map map to check the initial player direction
 * @param player player where fill the value
 */
static void	init_direction(t_map *map, t_player *player)
{
	char	direction_type;
	double	plane_length;

	direction_type = map->grid[(size_t)player->pos[Y]][(size_t)player->pos[X]];
	if (direction_type == 'N')
		player->dir_a = 270;
	else if (direction_type == 'S')
		player->dir_a = 90;
	else if (direction_type == 'E')
		player->dir_a = 0;
	else
		player->dir_a = 180;
	player->dir_vec[X] = cos(player->dir_a * M_PI / 180);
	player->dir_vec[Y] = sin(player->dir_a * M_PI / 180);
	plane_length = tan(70.0 * M_PI / 180 / 2.0);
	player->plane[X] = -player->dir_vec[Y] * plane_length;
	player->plane[Y] = player->dir_vec[X] * plane_length;
}

/**
 * @brief Init all the player information
 *
 * @param map reference map
 * @param player player where fill data
 * @return 0 if succes / 1 if error
 */
int	init_player(t_map *map, t_player *player)
{
	player->pos[X] = -1;
	player->pos[Y] = -1;
	player->mouse_x = -1;
	if (init_start_position(map, player))
	{
		if (player->pos[X] == -1)
			ft_dprintf(2, "Error\nNo starting position\n");
		return (1);
	}
	init_direction(map, player);
	player->speed = 1;
	return (0);
}
