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
 * @param line 
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
	res = fill_texture_2(line, mlx, textures);
	return (res);
}

/**
 * @brief Fill the color into textures struct at the correct emplacement
 *
 * @param color 
 * @param textures 
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

static int	fill_all(char *line, t_ctx *ctx)
{
	int	err_text_code;

	err_text_code = fill_texture(line, ctx->mlx, ctx->map->textures);
	if (err_text_code == 1)
	{
		if (fill_color(line, ctx->map->textures))
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
	while (loaded_texture++ < 7)
	{
		line = skip_empty_lines(fd);
		remove_spaces(line);
		if (fill_all(line, ctx))
			return (1);
		free(line);
	}
	return (0);
}
