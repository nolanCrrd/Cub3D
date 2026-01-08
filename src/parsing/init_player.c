#include <stddef.h>
#include "ft_printf.h"
#include "map.h"
#include "player.h"

static int	init_start_position(t_map *map, t_player *player)
{
	size_t	current_x;
	size_t	current_y;

	current_y = 0;
	while (current_y < map->size_y)
	{
		current_x = 0;
		while (current_x < map->size_x)
		{
			if (map->grid[current_y][current_x] == 'N' || map->grid[current_y][current_x] == 'S'
				|| map->grid[current_y][current_x] == 'E' || map->grid[current_y][current_x] == 'W')
			{
				if (player->pos[X] != -1)
				{
					ft_dprintf(2, "Error\nMultiple start position\n");
					return (1);
				}
				player->pos[X] = current_x;
				player->pos[Y] = current_y;
			}
			current_x++;
		}
		current_y++;
	}
	return (player->pos[X] == -1);
}

static void	init_direction(t_map *map, t_player *player)
{
	char	direction_type;

	direction_type = map->grid[(size_t)player->pos[Y]][(size_t)player->pos[X]];
	if (direction_type == 'N')
		player->direction_angle = 90;
	else if (direction_type == 'S')
		player->direction_angle = 270;
	else if (direction_type == 'E')
		player->direction_angle = 0;
	else
		player->direction_angle = 180;
}

int	init_player(t_map *map, t_player *player)
{
	player->pos[X] = -1;
	player->pos[Y] = -1;
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