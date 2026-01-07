#include "parsing.h"
#include "map.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

t_map	*parse(char *file_path)
{
	t_map	*map;
	int		fd;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
	{
		perror("cub3D");
		return (NULL);
	}
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("cub3D");
		return (NULL);
	}
	if (check_file(fd, map))
	{
		free(map);
		return (NULL);
	}
	printf("x:%d; y:%d\n", map->size_x, map->size_y);
	return (map);
}
