#include "ctx.h"
#include "ft_printf.h"
#include "libft.h"
#include "map.h"
#include <stddef.h>
#include <stdio.h>

void	destroy_map(t_map **map)
{
	size_t	current_y;

	current_y = 0;
	if ((*map)->grid)
	{
		while (current_y < (*map)->size_y)
			free((*map)->grid[current_y++]);
		free((*map)->grid);
	}
	if ((*map)->textures)
		printf("[TODO] Destroy texture on destroy map\n");
	free(*map);
	*map = NULL;
}

void	destroy_ctx(t_ctx **ctx)
{
	if ((*ctx)->map)
		destroy_map(&(*ctx)->map);
	free((*ctx)->player);
	free((*ctx));
	*ctx = NULL;
}

t_ctx	*init_ctx(char *file_path)
{
	t_ctx	*ctx;

	ctx = ft_calloc(1, sizeof(t_ctx));
	if (!ctx)
	{
		ft_dprintf(2, "Error\nUnable to init ctx\n");
		return (NULL);
	}
	ctx->map = ft_calloc(1, sizeof(t_map));
	ctx->player = ft_calloc(1, sizeof(t_player));
	if (!ctx->map || !ctx->player)
	{
		ft_dprintf(2, "Error\nUnable to init ctx\n");
		free(ctx->map);
		free(ctx->player);
		free(ctx);
		return (NULL);
	}
	ctx->map->file_path = file_path;
	ctx->mlx = mlx_init();
	return (ctx);
}
