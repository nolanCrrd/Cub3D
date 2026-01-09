#include "ctx.h"
#include "ft_printf.h"
#include "ctx.h"
#include "ft_printf/includes/ft_printf.h"
#include "parsing.h"
#include "map.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	check_file_extension(t_map *map)
{
	if (!ft_endwith(map->file_path, ".cub"))
	{
		ft_dprintf(2, "Error\nFile must be ending with .cub\n");
		return (1);
	}
	return (0);
}

t_ctx	*parse(char *file_path)
{
	t_ctx	*ctx;
	int		fd;

	ctx = init_ctx(file_path);
	if (!ctx || check_file_extension(ctx->map) || check_file(ctx->map))
	{
		destroy_ctx(&ctx);
		return (NULL);
	}
	fd = open(ctx->map->file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("cub3D");
		destroy_ctx(&ctx);
		return (NULL);
	}
	if (init_textures(fd, ctx) || init_map(fd, ctx->map)
		|| init_player(ctx->map, ctx->player) || is_valid_map(ctx->map))
	{
		close(fd);
		destroy_ctx(&ctx);
		return (NULL);
	}
	close(fd);

	// DEBUG
	printf("x:%zu; y:%zu\n", ctx->map->size_x, ctx->map->size_y);
	printf("C : {r: %i, g: %i, b: %i}\n",
			ctx->map->textures->ceiling->r,
			ctx->map->textures->ceiling->g,
			ctx->map->textures->ceiling->b);
	printf("F : {r: %i, g: %i, b: %i}\n",
			ctx->map->textures->floor->r,
			ctx->map->textures->floor->g,
			ctx->map->textures->floor->b);
	printf("PLAYER DATA : {x: %f, y: %f, direction: %f}\n", ctx->player->pos[X], ctx->player->pos[Y], ctx->player->direction_angle);
	show_map(ctx->map);
	return (ctx);
}
