#include "ft_printf.h"
#include "parsing.h"
#include "map.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

t_map	*parse(char *file_path)
{
	t_map	*map;

	if (!ft_endwith(file_path, ".cub"))
	{
		ft_dprintf(2, "Error\nFile must be ending with .cub\n");
		return (NULL);
	}
	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
	{
		perror("cub3D");
		return (NULL);
	}
	map->file_path = file_path;
	if (check_file(map))
	{
		free(map);
		return (NULL);
	}
	printf("x:%d; y:%d\n", map->size_x, map->size_y);
	return (map);
}
