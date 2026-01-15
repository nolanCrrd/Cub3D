/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:39:21 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 10:39:49 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "mlx.h"
#include "ctx.h"

/**
 * @brief Rotete the player based on his mouse movement
 *
 * @param ctx global context of cub3d
 */
void	player_mouse_rotate(t_ctx *ctx)
{
	int	mouse_y;
	int	mouse_x;

	mlx_mouse_get_pos(ctx->mlx, &mouse_x, &mouse_y);
	if (ctx->player->mouse_x == -1)
	{
		ctx->player->as_moved = 0;
		ctx->player->mouse_x = mouse_x;
		return ;
	}
	if (ctx->player->mouse_x == mouse_x)
	{
		ctx->player->as_moved = 0;
		return ;
	}
	rotate_dir(ctx->player->dir_vec, ctx->player->plane, -(double)
		(ctx->player->mouse_x - mouse_x) * (ctx->frame_time / 1000.0) * 0.05);
	mlx_mouse_move(ctx->mlx, ctx->win, WIN_W / 2, WIN_H / 2);
	ctx->player->mouse_x = WIN_W / 2;
	ctx->player->as_moved = 1;
}
