#include "ctx.h"
#include "mlx.h"
#include "render.h"
#include "utils.h"

void	update(void *ptr)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ptr;
	ctx->old_frame = ctx->frame;
	refresh_frame_time(ctx);
	player_mouse_rotate(ctx);
	player_move(ctx);
	player_rotate(ctx);
	raycaster(ctx);
	mlx_clear_window(ctx->mlx, ctx->win, (mlx_color){.rgba = 0});
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->render, 0, 0);
	display_border(ctx);
	display_map(ctx);
	if (get_near_elmt(ctx->map->grid, "D", ctx->player->pos))
		mlx_string_put(ctx->mlx, ctx->win, 10, 300, (mlx_color){
			.rgba = 0x000000FF}, "E: Open door");
	if (get_near_elmt(ctx->map->grid, "O", ctx->player->pos))
		mlx_string_put(ctx->mlx, ctx->win, 10, 300, (mlx_color){
			.rgba = 0x000000FF}, "E: Close door");
}
