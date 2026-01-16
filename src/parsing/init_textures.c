/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:39:37 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 10:39:49 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "ft_printf.h"
#include "map.h"
#include "utils.h"
#include "libft.h"
#include "parsing.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Return the texture in the struct based based on the given filepath
 *
 * @param path 
 * @param mlx 
 * @return texture with mlx_image / null if not found
 */
t_texture	*get_texture(char *path, mlx_context mlx)
{
	t_texture	*new_texture;

	new_texture = malloc(sizeof(t_texture));
	if (new_texture == NULL)
	{
		perror("cub3D");
		return (NULL);
	}
	new_texture->texture = mlx_new_image_from_file(mlx,
			path, &new_texture->width, &new_texture->height);
	return (new_texture);
}

/**
 * @brief Create and add the texture to the textures struct at the correct
 * emplacement
 *
 * @param line line where is the texture path
 * @param mlx global mlx context
 * @param textures struct that will contain all the game textures
 * @return 1 if not wll texture / 2 if mlx error / 0 else
 */
static int	fill_texture(char *line, mlx_context mlx, t_textures *textures)
{
	if (line[0] == 'N')
	{
		textures->north = get_texture(line + 2, mlx);
		return ((textures->north == NULL
				|| textures->north->texture == NULL) * 2);
	}
	else if (line[0] == 'S')
	{
		textures->south = get_texture(line + 2, mlx);
		return ((textures->south == NULL
				|| textures->south->texture == NULL) * 2);
	}
	else if (line[0] == 'E')
	{
		textures->east = get_texture(line + 2, mlx);
		return ((textures->east == NULL
				|| textures->east->texture == NULL) * 2);
	}
	else if (line[0] == 'W')
	{
		textures->west = get_texture(line + 2, mlx);
		return ((textures->west == NULL
				|| textures->west->texture == NULL) * 2);
	}
	return (1);
}

/**
 * @brief Fill the color into textures struct at the correct emplacement
 *
 * @param color line that contain the rgb information
 * @param textures struct that contain all the game textures
 * @return 1 if error / 0 else
 */
static int	fill_color(char *color, t_textures *textures)
{
	mlx_color	*new_color;
	int			is_floor;

	new_color = malloc(sizeof(mlx_color));
	if (!new_color || !*color || !is_valid_rgb(color))
	{
		free(new_color);
		return (1);
	}
	is_floor = color[0] == 'F';
	new_color->r = ft_atoi(color + 1, NULL);
	color = ft_strchr(color, ',') + 1;
	new_color->g = ft_atoi(color, NULL);
	color = ft_strchr(color, ',') + 1;
	new_color->b = ft_atoi(color, NULL);
	new_color->a = 0xFF;
	if (is_floor)
		textures->floor = new_color;
	else
		textures->ceiling = new_color;
	return (0);
}

/**
 * @brief Fill all the map texture based if itś rgb code
 * or tyexture's path
 *
 * @param line 
 * @param ctx 
 * @return 
 */
static int	fill_all(char *line, t_ctx *ctx)
{
	int	err_text_code;

	err_text_code = fill_texture(line, ctx->mlx, ctx->textures);
	if (err_text_code == 1)
	{
		if (fill_color(line, ctx->textures))
		{
			free(line);
			ft_dprintf(2, "cub3D: Color not respect rgb format\n");
			return (1);
		}
	}
	else if (err_text_code == 2)
	{
		free(line);
		ft_dprintf(2, "cub3D: Error while loading texture\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Init all the texture (wall)
 *
 * @param fd file where texture are indicated
 * @param ctx global cub3d context
 * @return 1 if loading error / 0 else
 */
int	init_textures(int fd, t_ctx *ctx)
{
	char		*line;
	int			loaded_texture;

	ctx->textures = ft_calloc(1, sizeof(t_textures));
	if (ctx->textures == NULL)
	{
		perror("cub3D");
		return (1);
	}
	loaded_texture = 0;
	while (loaded_texture++ < 6)
	{
		line = skip_empty_lines(fd);
		remove_spaces(line);
		if (fill_all(line, ctx))
			return (1);
		free(line);
	}
	return (0);
}
