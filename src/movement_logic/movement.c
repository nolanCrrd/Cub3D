#include "ctx.h"

// TODO: Probleme de colision chelou
void	player_move(t_ctx *ctx)
{
	double	move_speed;

	move_speed = ctx->frame_time / 1000.0 * ctx->player->speed;
	if (ctx->player->movement[0] && !ctx->player->movement[1])
	{
		if (ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			+ ctx->player->dir_vec[X] * move_speed)] == '0')
			ctx->player->pos[X] += ctx->player->dir_vec[X] * move_speed;
		if (ctx->map->grid[(int)(ctx->player->pos[Y] + ctx->player->dir_vec[Y]
			* move_speed)][(int)(ctx->player->pos[X])] == '0')
			ctx->player->pos[Y] += ctx->player->dir_vec[Y] * move_speed;
	}
	if (!ctx->player->movement[0] && ctx->player->movement[1])
	{
		if (ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			- ctx->player->dir_vec[X] * move_speed)] == '0')
			ctx->player->pos[X] -= ctx->player->dir_vec[X] * move_speed;
		if (ctx->map->grid[(int)(ctx->player->pos[Y] - ctx->player->dir_vec[Y]
			* move_speed)][(int)(ctx->player->pos[X])] == '0')
			ctx->player->pos[Y] -= ctx->player->dir_vec[Y] * move_speed;
	}
	if (ctx->player->movement[2] && !ctx->player->movement[3])
	{
		if (ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			+ ctx->player->dir_vec[Y] * move_speed)] == '0')
			ctx->player->pos[X] += ctx->player->dir_vec[Y] * move_speed;
		if (ctx->map->grid[(int)(ctx->player->pos[Y] - ctx->player->dir_vec[X]
			* move_speed)][(int)(ctx->player->pos[X])] == '0')
			ctx->player->pos[Y] -= ctx->player->dir_vec[X] * move_speed;
	}
	if (!ctx->player->movement[2] && ctx->player->movement[3])
	{
		if (ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			- ctx->player->dir_vec[Y] * move_speed)] == '0')
			ctx->player->pos[X] -= ctx->player->dir_vec[Y] * move_speed;
		if (ctx->map->grid[(int)(ctx->player->pos[Y] + ctx->player->dir_vec[X]
			* move_speed)][(int)(ctx->player->pos[X])] == '0')
			ctx->player->pos[Y] += ctx->player->dir_vec[X] * move_speed;
	}
}
