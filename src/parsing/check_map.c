#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "utils.h"
#include "map.h"

int	check_walls_textures(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL || ft_strncmp(line, "NO ", 3) != 0)
		return (1);
	free(line);
	line = get_next_line(fd);
	if (line == NULL || ft_strncmp(line, "SO ", 3) != 0)
		return (1);
	free(line);
	line = get_next_line(fd);
	if (line == NULL || ft_strncmp(line, "WE ", 3) != 0)
		return (1);
	free(line);
	line = get_next_line(fd);
	if (line == NULL || ft_strncmp(line, "EA ", 3) != 0)
		return (1);
	free(line);
	return (0);
}

int	check_other_textures(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL || ft_strncmp(line, "F ", 2) != 0)
		return (1);
	free(line);
	line = get_next_line(fd);
	if (line == NULL || ft_strncmp(line, "C ", 2) != 0)
		return (1);
	free(line);
	return (0);
}

void	skip_empty_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && is_blank(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

int	check_map(int fd, t_map *map)
{
	char *line;
	int		x_max;
	int		y_max;
	int		tmp_x;

	x_max = 0;
	y_max = 0;
	if (check_walls_textures(fd))
		return (1);
	skip_empty_line(fd);
	if (check_other_textures(fd))
		return (1);
	skip_empty_line(fd);
	line = get_next_line(fd);
	while (line)
	{
		tmp_x = ft_strlen(line) - (ft_strchr(line, '\n') != NULL);
		if (tmp_x > x_max)
			x_max = tmp_x;
		y_max++;
		free(line);
		line = get_next_line(fd);
	}
	if (y_max < 3)
		return (-1);
	return (0);
}

