#include "ctx.h"
#include "math.h"

void	rotate_dir(double *dir, double *plane, double r_speed)
{
	double	old_dir[2];
	double	old_plane[2];

	old_dir[X] = dir[X];
	old_dir[Y] = dir[Y];
	old_plane[X] = plane[X];
	old_plane[Y] = plane[Y];
	dir[X] = old_dir[X] * cos(r_speed)
		- old_dir[Y] * sin(r_speed);
	dir[Y] = old_dir[X] * sin(r_speed)
		+ old_dir[Y] * cos(r_speed);
	plane[X] = old_plane[X] * cos(r_speed)
		- old_plane[Y] * sin(r_speed);
	plane[Y] = old_plane[X] * sin(r_speed)
		+ old_plane[Y] * cos(r_speed);
}

void	player_rotate(t_ctx *ctx)
{
	double	rotate_speed;

	rotate_speed = (ctx->frame - ctx->old_frame) / 1000 * P_R_SPEED;
	if (ctx->player->rotate[1])
		rotate_dir(ctx->player->dir_vec, ctx->player->plane, -rotate_speed);
	if (ctx->player->rotate[0])
		rotate_dir(ctx->player->dir_vec, ctx->player->plane, rotate_speed);
}
