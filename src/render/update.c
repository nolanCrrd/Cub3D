#include "ctx.h"
#include "libft.h"
#include "mlx.h"
#include "player.h"
#include "render.h"
#include "utils.h"
#include <stdio.h>

int	is_player_moved(t_player *player)
{
	return (
		player->movement[0] || player->movement[1]
		|| player->movement[2] || player->movement[3]
		|| player->rotate[0] || player->rotate[1]
	);
}

void	update(void *ptr)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ptr;
	ctx->old_frame = ctx->frame;
	refresh_frame_time(ctx);
	player_move(ctx);
	player_rotate(ctx);
	if (is_player_moved(ctx->player))
		raycaster(ctx);
	mlx_clear_window(ctx->mlx, ctx->win, (mlx_color){.rgba = 0});
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->render, 0, 0);
}
