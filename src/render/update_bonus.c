#include "ctx.h"
#include "libft.h"
#include "mlx.h"
#include "render.h"
#include "utils.h"
#include <stdio.h>

void update(void *ptr)
{
	t_ctx *ctx;

	ctx = (t_ctx *)ptr;
	ctx->old_frame = ctx->frame;
	refresh_frame_time(ctx);
	player_mouse_rotate(ctx);
	player_move(ctx);
	player_rotate(ctx);
	raycaster(ctx);

	//fps countewr for testing
	static int frame_count = 0;
	static char *test = NULL;
	if (frame_count % 50 == 0)
	{
		free(test);
		test = ft_itoa(1000 / ctx->frame_time);
	}
	mlx_clear_window(ctx->mlx, ctx->win, (mlx_color){.rgba = 0});
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->render, 0, 0);
	mlx_string_put(ctx->mlx, ctx->win, 30, 30, (mlx_color){.rgba = 0xFFFFFFFF}, test);
	frame_count++;
}
