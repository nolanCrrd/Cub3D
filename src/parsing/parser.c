#include "ctx.h"
#include "ft_printf.h"
#include "ctx.h"
#include "ft_printf/includes/ft_printf.h"
#include "parsing.h"
#include "map.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	checker(t_map *map)
{
	if (!ft_endwith(map->file_path, ".cub"))
	{
		ft_dprintf(2, "Error\nFile must be ending with .cub\n");
		return (1);
	}
	if (check_file(map))
	{
		free(map);
		return (1);
	}
	return (0);
}

t_ctx	*parse(char *file_path)
{
	t_ctx	*ctx;
	int		fd;

	ctx = init_ctx(file_path);
	if (!ctx || checker(ctx->map))
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
	init_textures(fd, ctx);
	init_map(fd, ctx->map);
	printf("x:%zu; y:%zu\n", ctx->map->size_x, ctx->map->size_y);
	ft_printf("C : {r: %i, g: %i, b: %i}\n",
			ctx->map->textures->ceiling->r,
			ctx->map->textures->ceiling->g,
			ctx->map->textures->ceiling->b);
	ft_printf("C : {r: %i, g: %i, b: %i}\n",
			ctx->map->textures->floor->r,
			ctx->map->textures->floor->g,
			ctx->map->textures->floor->b);
	return (ctx);
}
