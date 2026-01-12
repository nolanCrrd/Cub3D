#include "map.h"

char	get_tile(t_map *map, size_t x, size_t y)
{
	if (x >= map->size_x || y >= map->size_y)
		return (' ');
	return (map->grid[y][x]);
}