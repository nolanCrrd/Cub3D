#include <stdio.h>
#include "render.h"
#include "mlx.h"
#include "ctx.h"

void	player_mouse_rotate(t_ctx *ctx)
{
	int	mouse_y;
	int mouse_x;

	mlx_mouse_get_pos(ctx->mlx, &mouse_x, &mouse_y);
	if (ctx->player->mouse_x == -1)
	{
		ctx->player->mouse_x = mouse_x;
		return ;
	}
	if (ctx->player->mouse_x == mouse_x)
		return ;
	rotate_dir(ctx->player->dir_vec, ctx->player->plane, -(double)(ctx->player->mouse_x - mouse_x) * (ctx->frame_time / 1000.0) * 0.05);
	mlx_mouse_move(ctx->mlx, ctx->win, WIN_W / 2, WIN_H / 2);
	ctx->player->mouse_x = WIN_W / 2;
}