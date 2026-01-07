#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include "ft_printf.h"
#include "libft.h"
#include "map.h"

static int	init_grid(t_map *map)
{
	size_t	i;

	i = 0;
	map->grid = ft_calloc(map->size_y + 1, sizeof(char));
	if (!map->grid)
		return (1);
	while (i < map->size_x)
	{
		map->grid[i] = ft_calloc(map->size_x + 1, sizeof(char));
		if (!map->grid[i])
		{
			while (i)
				free(map->grid[i--]);
			free(map->grid);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	fill_grid(t_map *map, int fd)
{

}

static void	move_file_cursor_to_map(int fd)
{
	
}

int	init_map(t_map *map)
{
	int	fd;

	if (init_grid(map))
	{
		ft_dprintf(2, "Error\nUnable to init grid\n");
		return (1);
	}
	fd = open(map->file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("cub3D");
		return (1);
	}
}