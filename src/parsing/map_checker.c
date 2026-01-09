#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "map.h"

char	get_tile(t_map *map, size_t x, size_t y)
{
	if (x >= map->size_x || y >= map->size_y)
		return (' ');
	return (map->grid[y][x]);
}

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
				|| tile == 'E' || tile == 'W')
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

int	is_valid_map(t_map *map)
{
	if (!is_playable(map))
	{
		ft_dprintf(2, "Error\nMap is not playable\n");
		return (1);
	}
	return (0);
}
