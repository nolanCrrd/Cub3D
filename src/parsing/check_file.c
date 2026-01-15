/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:39:27 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 15:41:30 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft_printf.h"
#include "get_next_line.h"
#include "libft.h"
#include "utils.h"
#include "map.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Tell if the line contain a valid texture and if it
 * wasn't already already_seen and add it to texture already seen
 *
 * @param line
 * @param already_seen 
 * @return 
 */
static int	is_valid_texture(char *line, char **already_seen)
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
				if (ft_strncmp(line, already_seen[j],
						ft_strlen(already_seen[j])) == 0)
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

/**
 * @brief Check if the config file contain all the needed textures
 *
 * @param fd map file to check
 * @param already_seen array that contain all seen textures
 * @return 0 if texture loaded / 1 if error in file
 */
static int	check_textures(int fd, char **already_seen)
{
	char	*line;
	size_t	i;

	i = 0;
	while (i < 6)
	{
		line = skip_empty_lines(fd);
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

/**
 * @brief Check if the file contain a map without empty line in
 * and it's store the size of the map into the strcut
 *
 * @param fd map file to check
 * @param map all map data
 * @return 0 if map is valid / 0 else
 */
static int	check_map(int fd, t_map *map)
{
	char	*line;
	int		x_max;
	int		tmp_x;

	x_max = 0;
	line = skip_empty_lines(fd);
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
	free(line);
	map->size_x = x_max;
	return (0);
}

/**
 * @brief Check all the map file
 *
 * @param map map structure
 * @return 0 if map is valide / 1 else
 */
int	check_file(t_map *map)
{
	char	**already_seen;
	int		fd;
	int		err_code;

	fd = open(map->file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("cub3D");
		return (1);
	}
	already_seen = ft_calloc(7, sizeof(char *));
	if (!already_seen)
	{
		perror("cub3D");
		free(already_seen);
		finish_get_next_line(fd);
		close(fd);
		return (1);
	}
	err_code = check_textures(fd, already_seen) || check_map(fd, map);
	if (err_code)
		finish_get_next_line(fd);
	free(already_seen);
	close(fd);
	return (err_code);
}
