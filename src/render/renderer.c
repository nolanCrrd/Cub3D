#include "ctx.h"
#include "mlx.h"
#include "render.h"
#include "libft.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>
#include <stdbool.h>

/**
 * @brief Init all the mlx related data
 *
 * @param ctx global cub3d context
 */
static void	init_render(t_ctx *ctx)
{
	mlx_window_create_info	info;
	struct timeval			tv;

	ft_bzero(&info, sizeof(info));
	info.height = WIN_H;
	info.width = WIN_W;
	info.title = "cub3D";
	info.is_resizable = false;
	ctx->win = mlx_new_window(ctx->mlx, &info);
	mlx_set_fps_goal(ctx->mlx, 120);
	mlx_on_event(ctx->mlx, ctx->win, MLX_WINDOW_EVENT, close_hook, ctx);
	mlx_on_event(ctx->mlx, ctx->win, MLX_KEYDOWN, all_keydown_hooks, ctx);
	mlx_on_event(ctx->mlx, ctx->win, MLX_KEYUP, all_keyup_hooks, ctx);
	mlx_mouse_hide(ctx->mlx);
	mlx_add_loop_hook(ctx->mlx, update, ctx);
	gettimeofday(&tv, NULL);
	ctx->frame = tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
	ctx->old_frame = ctx->frame;
	ctx->render = mlx_new_image(ctx->mlx, WIN_W, WIN_H);
	mlx_set_font_scale(ctx->mlx, "default", 24);
}

int	render_cub3d(t_ctx *ctx)
{
	init_render(ctx);
	raycaster(1, ctx);
	mlx_loop(ctx->mlx);
	return (1);
}
