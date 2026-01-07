#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "utils.h"
#include "ft_printf.h"
#include "libft.h"
#include "map.h"

static int	init_grid(t_map *map)
{
	size_t	i;

	map->grid = ft_calloc(map->size_y + 1, sizeof(char *));
	if (!map->grid)
		return (1);
	i = 0;
	while (i < map->size_y)
	{
		printf("%lu/%lu\n", i, map->size_y);
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
	char	*line;
	size_t	current_x;
	size_t	current_y;

	line = skip_empty_lines(fd);
	current_y = 0;
	while (line && current_y < map->size_y)
	{
		current_x = 0;
		while (current_x < ft_strlen(line) - (ft_strchr(line, '\n') != NULL))
		{
			map->grid[current_y][current_x] = line[current_x];
			current_x++;
		}
		while (current_x < map->size_x)
		{
			map->grid[current_y][current_x] = ' ';
			current_x++;
		}
		current_y++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

static void	move_file_cursor_to_map(int fd)
{
	size_t	i;

	i = 0;
	while (i < 6)
	{
		i++;
		skip_empty_lines(fd);
	}
}

static void	show_map(t_map *map)
{
	size_t	current_x;
	size_t	current_y;

	current_y = 0;
	while (current_y < map->size_y)
	{
		current_x = 0;
		while (current_x < map->size_x)
		{
			printf("%c", map->grid[current_y][current_x]);
			current_x++;
		}
		printf("|\n");
		current_y++;
	}
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
	move_file_cursor_to_map(fd);
	fill_grid(map, fd);
	close(fd);
	show_map(map);
	return (0);
}