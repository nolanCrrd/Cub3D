#include "ctx.h"
#include "libft.h"

static void	player_strafe(char *walkable, double move_speed, t_ctx *ctx)
{
	if (ctx->player->movement[2] && !ctx->player->movement[3])
	{
		if (ft_strchr(walkable, ctx->map->grid[(int)ctx->player->pos[Y]][
				(int)(ctx->player->pos[X]
				+ ctx->player->dir_vec[Y] * move_speed)]))
			ctx->player->pos[X] += ctx->player->dir_vec[Y] * move_speed;
		if (ft_strchr(walkable, ctx->map->grid[(int)(ctx->player->pos[Y]
					- ctx->player->dir_vec[X] * move_speed)]
			[(int)(ctx->player->pos[X])]))
			ctx->player->pos[Y] -= ctx->player->dir_vec[X] * move_speed;
	}
	if (!ctx->player->movement[2] && ctx->player->movement[3])
	{
		if (ft_strchr(walkable, ctx->map->grid[(int)ctx->player->pos[Y]][(int)
				(ctx->player->pos[X] - ctx->player->dir_vec[Y] * move_speed)]))
			ctx->player->pos[X] -= ctx->player->dir_vec[Y] * move_speed;
		if (ft_strchr(walkable, ctx->map->grid[(int)(ctx->player->pos[Y]
					+ ctx->player->dir_vec[X] * move_speed)][
			(int)(ctx->player->pos[X])]))
			ctx->player->pos[Y] += ctx->player->dir_vec[X] * move_speed;
	}
}

// TODO: Probleme de colision chelou
void	player_move(t_ctx *ctx)
{
	double		m_s;
	const char	*walkable = "0O";

	m_s = ctx->frame_time / 1000.0 * ctx->player->speed;
	if (ctx->player->movement[0] && !ctx->player->movement[1])
	{
		if (ft_strchr(walkable, ctx->map->grid[(int)ctx->player->pos[Y]][
				(int)(ctx->player->pos[X] + ctx->player->dir_vec[X] * m_s)]))
			ctx->player->pos[X] += ctx->player->dir_vec[X] * m_s;
		if (ft_strchr(walkable, ctx->map->grid[(int)(ctx->player->pos[Y] + ctx
					->player->dir_vec[Y] * m_s)][(int)(ctx->player->pos[X])]))
			ctx->player->pos[Y] += ctx->player->dir_vec[Y] * m_s;
	}
	if (!ctx->player->movement[0] && ctx->player->movement[1])
	{
		if (ft_strchr(walkable, ctx->map->grid[(int)ctx->player->pos[Y]][
				(int)(ctx->player->pos[X]
				- ctx->player->dir_vec[X] * m_s)]))
			ctx->player->pos[X] -= ctx->player->dir_vec[X] * m_s;
		if (ft_strchr(walkable, ctx->map->grid[(int)(ctx->player->pos[Y]
					- ctx->player->dir_vec[Y] * m_s)][
			(int)(ctx->player->pos[X])]))
			ctx->player->pos[Y] -= ctx->player->dir_vec[Y] * m_s;
	}
	player_strafe((char *)walkable, m_s, ctx);
}
