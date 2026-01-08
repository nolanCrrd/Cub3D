#include "ctx.h"
#include "ft_printf/includes/ft_printf.h"
#include "map.h"
#include "utils.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

static t_texture	*get_texture(char *path, mlx_context mlx)
{
	t_texture	*new_texture;
	
	new_texture = malloc(sizeof(t_texture));
	if (new_texture == NULL)
	{
		perror("cub3D");
		return (NULL);
	}
	new_texture->texture = mlx_new_image_from_file(mlx, path, &new_texture->width, &new_texture->height);
	return (new_texture);
}

int	fill_texture(char *line, mlx_context mlx, t_textures *textures)
{
	if (line[0] == 'N')
	{
		textures->north = get_texture(line + 2, mlx);
		if (textures->north == NULL)
			return (2);
	}
	else if (line[0] == 'S')
	{
		textures->south = get_texture(line + 2, mlx);
		if (textures->north == NULL)
			return (2);
	}
	else if (line[0] == 'E')
	{
		textures->east = get_texture(line + 2, mlx);
		if (textures->north == NULL)
			return (2);
	}
	else if (line[0] == 'W')
	{
		textures->west = get_texture(line + 2, mlx);
		if (textures->north == NULL)
			return (2);
	}
	else
		return (1);
	return (0);
}

static int	is_valid_color(char *color)
{
	int	as_overflow;

	if (ft_isdigit(color[0]))
	{
		if (ft_atoi(color, &as_overflow) > 255 || as_overflow)
			return (0);
	}
	color = ft_strchr(color, ',');
	if (color++ == NULL || !*color)
		return (0);
	if (ft_isdigit(color[0]))
	{
		if (ft_atoi(color, &as_overflow) > 255 || as_overflow)
			return (0);
	}
	color = ft_strchr(color, ',');
	if (color++ == NULL || !*color)
		return (0);
	if (ft_isdigit(color[0]))
	{
		if (ft_atoi(color, &as_overflow) > 255 || as_overflow)
			return (0);
	}
	return (1);
}

static int	fill_color(char *color, t_textures *textures)
{
	mlx_color	*new_color;
	int			is_floor;

	new_color = malloc(sizeof(mlx_color));
	if (!new_color || !*color || !is_valid_color(color))
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

int	init_textures(int fd, t_ctx *ctx)
{
	char		*line;
	int			loaded_texture;
	int			err_text_code;

	ctx->map->textures = ft_calloc(1, sizeof(t_textures));
	if (ctx->map->textures == NULL)
	{
		perror("cub3D");
		return (1);
	}
	loaded_texture = 0;
	while (loaded_texture < 6)
	{
		line = skip_empty_lines(fd);
		remove_spaces(line);
		err_text_code = fill_texture(line, ctx->mlx, ctx->map->textures);
		if (err_text_code == 1)
			fill_color(line, ctx->map->textures);
		else if (err_text_code == 2)
			// return (1);
		free(line);
		loaded_texture++;
	}
	return (0);
}
