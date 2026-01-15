/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:39:23 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 10:39:49 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"

/**
 * @brief Make the player move on strafe side
 *
 * @param walkable charset that contain all map accessible char
 * @param move_speed player move_speed (based on the frame_time)
 * @param ctx global context of cub3d
 */
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

/**
 * @brief Make the player move in all direction
 *
 * @param ctx global cub3d context
 */
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
