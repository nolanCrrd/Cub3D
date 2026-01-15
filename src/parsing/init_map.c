/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:39:31 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 10:39:49 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "utils.h"
#include "ft_printf.h"
#include "libft.h"
#include "map.h"

/**
 * @brief Allocate the map grid
 *
 * @param map map where allocate the grid
 * @return 0 if sucess / 0 else
 */
static int	init_grid(t_map *map)
{
	size_t	i;

	map->grid = ft_calloc(map->size_y + 1, sizeof(char *));
	if (!map->grid)
		return (1);
	i = 0;
	while (i < map->size_y)
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

/**
 * @brief Fill all the map grid with the file data
 *
 * @param map map where grid is stored
 * @param fd reference file
 */
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

void	show_map(t_map *map)
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

int	init_map(int fd, t_map *map)
{
	if (init_grid(map))
	{
		ft_dprintf(2, "Error\nUnable to init grid\n");
		return (1);
	}
	fill_grid(map, fd);
	return (0);
}
