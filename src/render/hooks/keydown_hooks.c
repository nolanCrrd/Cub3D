/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:47:40 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 10:55:37 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "key.h"
#include "mlx.h"
#include "player.h"
#include "utils.h"
#include <endian.h>
#include <stddef.h>

/**
 * @brief Handle all movement W/A/S/D
 *
 * @param key 
 * @param ctx 
 */
static void	player_movement(int key, t_ctx *ctx)
{
	if (key == KEY_W)
		ctx->player->movement[0] = 1;
	if (key == KEY_S)
		ctx->player->movement[1] = 1;
	if (key == KEY_A)
		ctx->player->movement[2] = 1;
	if (key == KEY_D)
		ctx->player->movement[3] = 1;
	if (key == KEY_SHIFT)
		ctx->player->speed = P_M_SPEED * 2;
}

/**
 * @brief Handle rotate arrow
 *
 * @param key 
 * @param ctx 
 */
static void	rotate_player(int key, t_ctx *ctx)
{
	if (key == KEY_LEFT)
		ctx->player->rotate[1] = 1;
	if (key == KEY_RIGHT)
		ctx->player->rotate[0] = 1;
}

/**
 * @brief Handle the open door if one nearby
 *
 * @param key 
 * @param ctx 
 */
static void	open_door(int key, t_ctx *ctx)
{
	int		*near_door;
	double	*pos;
	char	**grid;

	if (key == KEY_E)
	{
		pos = ctx->player->pos;
		grid = ctx->map->grid;
		near_door = get_near_elmt(ctx->map->grid, "DO", pos);
		if (!near_door || (near_door[X] == 0 && near_door[Y] == 0))
			return ;
		if (grid[(int)pos[Y] + near_door[Y]]
			[(int)pos[X] + near_door[X]] == 'D')
			grid[(int)pos[Y] + near_door[Y]][(int)pos[X] + near_door[X]] = 'O';
		else if (grid[(int)pos[Y] + near_door[Y]]
			[(int)pos[X] + near_door[X]] == 'O')
			grid[(int)pos[Y] + near_door[Y]][(int)pos[X] + near_door[X]] = 'D';
	}
}

/**
 * @brief Listen to all valid key input
 *
 * @param key 
 * @param ptr global cub3d context
 */
void	all_keydown_hooks(int key, void *ptr)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ptr;
	player_movement(key, ctx);
	rotate_player(key, ctx);
	open_door(key, ctx);
	if (key == KEY_ESC)
	{
		ctx->player->is_dead = 1;
		mlx_loop_end(ctx->mlx);
	}
	if (key == KEY_PLUS)
		ctx->lod_value++;
	if (key == KEY_MINUS)
		ctx->lod_value--;
	if (ctx->lod_value < 1)
		ctx->lod_value = 1;
}
