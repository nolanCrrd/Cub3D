#include "map.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

t_map	*get_map(char *file_path)
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
		
	}
	return (map);
}
