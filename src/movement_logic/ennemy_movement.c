#include "ctx.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

void	ennemy_move(t_ctx *ctx)
{
	const char *walkable = "0OM";
	double	distance;
	double	direction[2];
	double	m_s;

	m_s = ctx->frame_time / 1000.0 * E_M_SPEED;
	direction[X] = ctx->player->pos[X] - ctx->ennemy->pos[X];
	direction[Y] = ctx->player->pos[Y] - ctx->ennemy->pos[Y];
	distance = sqrt(direction[X] * direction[X] + direction[Y] * direction[Y]);
	if (distance <= 0.2)
	{
		ctx->player->is_dead = 1;
		return ;
	}
	direction[X] /= distance;
	direction[Y] /= distance;
	printf("%f;%f\n", direction[X], direction[Y]);

	if (ft_strchr(walkable, ctx->map->grid[(int)ctx->ennemy->pos[Y]][
			(int)(ctx->ennemy->pos[X] + direction[X] * m_s)]))
		ctx->ennemy->pos[X] += direction[X] * m_s;
	if (ft_strchr(walkable, ctx->map->grid[(int)(ctx->ennemy->pos[Y] + direction[Y]
			   * m_s)][(int)(ctx->ennemy->pos[X])]))
		ctx->ennemy->pos[Y] += direction[Y] * m_s;
}
