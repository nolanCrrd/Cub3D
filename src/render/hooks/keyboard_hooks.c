#include "ctx.h"
#include "key.h"
#include "player.h"
#include <endian.h>
#include <math.h>
#include <stdio.h>

static void	player_movement(int key, t_ctx *ctx)
{
	double	move_speed;

	move_speed = (ctx->frame - ctx->old_frame) / 1000.0 * P_M_SPEED;
	if (key == KEY_W)
	{
		if (ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			+ ctx->player->dir_vec[X] * move_speed)] == '0')
			ctx->player->pos[X] += ctx->player->dir_vec[X] * move_speed;
		if (ctx->map->grid[(int)(ctx->player->pos[Y] + ctx->player->dir_vec[Y]
			* move_speed)][(int)(ctx->player->pos[X])] == '0')
			ctx->player->pos[Y] += ctx->player->dir_vec[Y] * move_speed;
	}
	if (key == KEY_S)
	{
		if (ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			- ctx->player->dir_vec[X] * move_speed)] == '0')
			ctx->player->pos[X] -= ctx->player->dir_vec[X] * move_speed;
		if (ctx->map->grid[(int)(ctx->player->pos[Y] - ctx->player->dir_vec[Y]
			* move_speed)][(int)(ctx->player->pos[X])] == '0')
			ctx->player->pos[Y] -= ctx->player->dir_vec[Y] * move_speed;
	}
	// TODO : Pouvoir strafe
	if (key == KEY_D)
	{
		if (ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			+ ctx->player->dir_vec[Y] * move_speed)] == '0')
			ctx->player->pos[X] += ctx->player->dir_vec[Y] * move_speed;
		if (ctx->map->grid[(int)(ctx->player->pos[Y] - ctx->player->dir_vec[X]
			* move_speed)][(int)(ctx->player->pos[X])] == '0')
			ctx->player->pos[Y] -= ctx->player->dir_vec[X] * move_speed;
	}
	if (key == KEY_A)
	{
		if (ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			- ctx->player->dir_vec[Y] * move_speed)] == '0')
			ctx->player->pos[X] -= ctx->player->dir_vec[Y] * move_speed;
		if (ctx->map->grid[(int)(ctx->player->pos[Y] + ctx->player->dir_vec[X]
			* move_speed)][(int)(ctx->player->pos[X])] == '0')
			ctx->player->pos[Y] += ctx->player->dir_vec[X] * move_speed;
	}
	printf("\ndirX:%f; dirY:%f;\tposX:%f ; posY:%f\n", ctx->player->dir_vec[X], ctx->player->dir_vec[Y], ctx->player->pos[X], ctx->player->pos[Y]);
}

static void rotate_dir(double *dir, double *plane, double r_speed)
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

static void	rotate_player(int key, t_ctx *ctx)
{
	double	rotate_speed;

	rotate_speed = (ctx->frame - ctx->old_frame) / 1000 * P_R_SPEED;
	if (key == KEY_LEFT)
		rotate_dir(ctx->player->dir_vec, ctx->player->plane, -rotate_speed);
	if (key == KEY_RIGHT)
		rotate_dir(ctx->player->dir_vec, ctx->player->plane, rotate_speed);
}

void	all_keyboard_hooks(int key, void *ptr)
{
	t_ctx *ctx;

	ctx = (t_ctx *)ptr;
	player_movement(key, ctx);
	rotate_player(key, ctx);
}
