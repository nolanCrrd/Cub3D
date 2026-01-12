#include "ctx.h"
#include "libft.h"

// TODO: Probleme de colision chelou
void	player_move(t_ctx *ctx)
{
	double	move_speed;
	const char	*walkable = "0O";

	move_speed = ctx->frame_time / 1000.0 * ctx->player->speed;
	if (ctx->player->movement[0] && !ctx->player->movement[1])
	{
		if (ft_strchr(walkable, ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			+ ctx->player->dir_vec[X] * move_speed)]))
			ctx->player->pos[X] += ctx->player->dir_vec[X] * move_speed;
		if (ft_strchr(walkable, ctx->map->grid[(int)(ctx->player->pos[Y] + ctx->player->dir_vec[Y]
			* move_speed)][(int)(ctx->player->pos[X])]))
			ctx->player->pos[Y] += ctx->player->dir_vec[Y] * move_speed;
	}
	if (!ctx->player->movement[0] && ctx->player->movement[1])
	{
		if (ft_strchr(walkable, ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			- ctx->player->dir_vec[X] * move_speed)]))
			ctx->player->pos[X] -= ctx->player->dir_vec[X] * move_speed;
		if (ft_strchr(walkable, ctx->map->grid[(int)(ctx->player->pos[Y] - ctx->player->dir_vec[Y]
			* move_speed)][(int)(ctx->player->pos[X])]))
			ctx->player->pos[Y] -= ctx->player->dir_vec[Y] * move_speed;
	}
	if (ctx->player->movement[2] && !ctx->player->movement[3])
	{
		if (ft_strchr(walkable, ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			+ ctx->player->dir_vec[Y] * move_speed)]))
			ctx->player->pos[X] += ctx->player->dir_vec[Y] * move_speed;
		if (ft_strchr(walkable, ctx->map->grid[(int)(ctx->player->pos[Y] - ctx->player->dir_vec[X]
			* move_speed)][(int)(ctx->player->pos[X])]))
			ctx->player->pos[Y] -= ctx->player->dir_vec[X] * move_speed;
	}
	if (!ctx->player->movement[2] && ctx->player->movement[3])
	{
		if (ft_strchr(walkable, ctx->map->grid[(int)ctx->player->pos[Y]][(int)(ctx->player->pos[X]
			- ctx->player->dir_vec[Y] * move_speed)]))
			ctx->player->pos[X] -= ctx->player->dir_vec[Y] * move_speed;
		if (ft_strchr(walkable, ctx->map->grid[(int)(ctx->player->pos[Y] + ctx->player->dir_vec[X]
			* move_speed)][(int)(ctx->player->pos[X])]))
			ctx->player->pos[Y] += ctx->player->dir_vec[X] * move_speed;
	}
}
