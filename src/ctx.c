#include "ctx.h"
#include "ft_printf.h"
#include "libft.h"
#include "map.h"
#include "mlx.h"
#include <stddef.h>
#include <stdio.h>

void	destroy_rec(t_ctx *ctx)
{
	if (!ctx->rec)
		return ;
	mlx_destroy_image(ctx->mlx, ctx->rec[0]);
	mlx_destroy_image(ctx->mlx, ctx->rec[1]);
	mlx_destroy_image(ctx->mlx, ctx->rec[2]);
	free(ctx->rec);
	ctx->rec = NULL;
}

void	destroy_textures(t_textures **textures, t_ctx *ctx)
{
	if ((*textures)->north && (*textures)->north->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->north->texture);
	free((*textures)->north);
	if ((*textures)->south && (*textures)->south->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->south->texture);
	free((*textures)->south);
	if ((*textures)->east && (*textures)->east->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->east->texture);
	free((*textures)->east);
	if ((*textures)->west && (*textures)->west->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->west->texture);
	free((*textures)->west);
	if ((*textures)->ceiling_tex && (*textures)->ceiling_tex->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->ceiling_tex->texture);
	free((*textures)->ceiling_tex);
	if ((*textures)->floor_tex && (*textures)->floor_tex->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->floor_tex->texture);
	free((*textures)->floor_tex);
	if ((*textures)->door && (*textures)->door->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->door->texture);
	free((*textures)->door);
	free((*textures)->ceiling);
	free((*textures)->floor);
	free(*textures);
	*textures = NULL;
}

void	destroy_map(t_map **map, t_ctx *ctx)
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
		destroy_textures(&(*map)->textures, ctx);
	free(*map);
	*map = NULL;
}

void	destroy_ctx(t_ctx **ctx)
{
	if ((*ctx)->map)
		destroy_map(&(*ctx)->map, *ctx);
	if ((*ctx)->render)
		mlx_destroy_image((*ctx)->mlx, (*ctx)->render);
	if ((*ctx)->win)
		mlx_destroy_window((*ctx)->mlx, (*ctx)->win);
	free((*ctx)->player);
	destroy_rec(*ctx);
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
	ctx->lod_value = 4;
	return (ctx);
}
