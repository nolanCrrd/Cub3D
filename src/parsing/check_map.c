#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "utils.h"
#include "map.h"

static char	*skip_empty_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && is_blank(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static int	check_walls_textures(int fd)
{
	char	*line;

	line = skip_empty_line(fd);
	if (line == NULL || ft_strncmp(line, "NO ", 3) != 0)
		return (1);
	free(line);
	line = skip_empty_line(fd);
	if (line == NULL || ft_strncmp(line, "SO ", 3) != 0)
		return (1);
	free(line);
	line = skip_empty_line(fd);
	if (line == NULL || ft_strncmp(line, "WE ", 3) != 0)
		return (1);
	free(line);
	line = skip_empty_line(fd);
	if (line == NULL || ft_strncmp(line, "EA ", 3) != 0)
		return (1);
	free(line);
	return (0);
}

static int	check_other_textures(int fd)
{
	char	*line;

	line = skip_empty_line(fd);
	if (line == NULL || ft_strncmp(line, "F ", 2) != 0)
		return (1);
	free(line);
	line = skip_empty_line(fd);
	if (line == NULL || ft_strncmp(line, "C ", 2) != 0)
		return (1);
	free(line);
	return (0);
}


int	check_map(int fd, t_map *map)
{
	char	*line;
	int		x_max;
	int		tmp_x;

	x_max = 0;
	if (check_walls_textures(fd))
		return (1);
	if (check_other_textures(fd))
		return (1);
	line = skip_empty_line(fd);
	while (line)
	{
		tmp_x = ft_strlen(line) - (ft_strchr(line, '\n') != NULL);
		if (tmp_x > x_max)
			x_max = tmp_x;
		map->size_y++;
		free(line);
		line = get_next_line(fd);
	}
	map->size_x = x_max;
	return (0);
}

