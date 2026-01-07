#include "map.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

t_map	*read_file(char *file_path)
{
	int		fd;
	char	*line;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Cub3d");
		return (NULL);
	}
}

t_map	*get_map(char *file_path)
{
	t_map *map;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
	{
		perror("Cub3d");
		return (NULL);
	}
	read_file(file_path);
	return (map);
}
