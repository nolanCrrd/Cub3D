/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:39:39 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 16:52:05 by ncorrear         ###   ########.fr       */
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
 * @brief Create and add the texture to the textures struct at the correct
 * emplacement
 *
 * @param
 * @param mlx 
 * @param textures 
 * @return 1 if not wll texture / 2 if mlx error / 0 else
 */
static int	fill_texture_2(char *line, mlx_context mlx, t_textures *textures)
{
	if (line[0] == 'W')
	{
		textures->west = get_texture(line + 2, mlx);
		return ((textures->west == NULL
				|| textures->west->texture == NULL) * 2);
	}
	else if (line[0] == 'D')
	{
		textures->door = get_texture(line + 2, mlx);
		return ((textures->door == NULL
				|| textures->door->texture == NULL) * 2);
	}
	else if (line[0] == 'F')
	{
		textures->floor_tex = get_texture(line + 1, mlx);
		return ((textures->floor_tex == NULL
				|| textures->floor_tex->texture == NULL) * 2);
	}
	else if (line[0] == 'C')
	{
		textures->ceiling_tex = get_texture(line + 1, mlx);
		return ((textures->ceiling_tex == NULL
				|| textures->ceiling_tex->texture == NULL) * 2);
	}
	return (1);
}

/**
 * @brief Create and add the texture to the textures struct at the correct
 * emplacement
 *
 * @param line 
 * @param mlx 
 * @param textures 
 * @return 1 if not wll texture / 2 if mlx error / 0 else
 */
static int	fill_texture(char *line, mlx_context mlx, t_textures *textures)
{
	int	res;

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
	else if (line[0] == 'M')
	{
		textures->ennemy = get_texture(line + 1, mlx);
		return ((textures->ennemy == NULL
				|| textures->ennemy->texture == NULL) * 1);
	}
	res = fill_texture_2(line, mlx, textures);
	return (res);
}

static int	fill_all(char *line, t_ctx *ctx)
{
	int	err_text_code;

	err_text_code = fill_texture(line, ctx->mlx, ctx->map->textures);
	if (err_text_code == 1)
	{
		free(line);
		ft_dprintf(2, "cub3D: Invalid texture\n");
		return (1);
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
 * @brief Init all the texture (wall and floor)
 *
 * @param fd 
 * @param ctx 
 * @return 1 if loading error / 0 else
 */
int	init_textures(int fd, t_ctx *ctx)
{
	char		*line;
	int			loaded_texture;

	ctx->map->textures = ft_calloc(1, sizeof(t_textures));
	if (ctx->map->textures == NULL)
	{
		perror("cub3D");
		return (1);
	}
	loaded_texture = 0;
	while (loaded_texture++ < 8)
	{
		line = skip_empty_lines(fd);
		remove_spaces(line);
		if (fill_all(line, ctx))
			return (1);
		free(line);
	}
	return (0);
}
