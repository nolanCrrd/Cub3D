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
	ctx->map->grid[(size_t)ctx->player->pos[Y]][(size_t)ctx->player->pos[X]] = '0';
	return (ctx);
}
