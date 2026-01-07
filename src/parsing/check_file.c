#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "utils.h"
#include "map.h"

static int is_valid_texture(char *line, char **already_seen)
{
	const char	*valid[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	size_t		i;
	size_t		j;

	i = -1;
	while (valid[++i])
	{
		if (ft_strncmp(line, valid[i], ft_strlen(valid[i])) == 0)
		{
			j = -1;
			while (already_seen[++j])
			{
				if (ft_strncmp(line, already_seen[j], ft_strlen(already_seen[j])) == 0)
				{
					ft_dprintf(2, "Error\nDuplicate texture (%s)\n", valid[i]);
					return (0);
				}
			}
			already_seen[j] = (char *)valid[i];
			return (1);
		}
	}
	ft_dprintf(2, "Error\nInvalid texture (%s)\n", line);
	return (0);
}

static int	check_textures(int fd, char **already_seen)
{
	char	*line;
	size_t	i;

	i = 0;
	while (i < 6)
	{
		line = skip_empty_line(fd);
		if (line == NULL)
		{
			ft_dprintf(2, "Error\nMissing necessary line\n");
			return (1);
		}
		remove_spaces(line);
		if (!is_valid_texture(line, already_seen))
		{
			free(line);
			return (1);
		}
		free(line);
		i++;
	}
	return (0);
}

int	check_map(int fd, t_map *map)
{
	char	*line;
	int		x_max;
	int		tmp_x;

	x_max = 0;
	line = skip_empty_line(fd);
	while (line)
	{
		if (is_blank(line))
		{
			ft_dprintf(2, "Error\nEmpty line in map\n");
			return (1);
		}
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

int	check_file(t_map *map)
{
	char	**already_seen;
	int		fd;

	fd = open(map->file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("cub3D");
		return (1);
	}
	already_seen = ft_calloc(7, sizeof(char *));
	if (check_textures(fd, already_seen) || check_map(fd, map))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}