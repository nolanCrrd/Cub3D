/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:05:17 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/16 15:57:51 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "mlx.h"
#include "player.h"
#include "render.h"
#include "utils.h"
#include "libft.h"
#include <stdio.h>

static void	render_door_text(t_ctx *ctx)
{
	if (get_near_elmt(ctx->map->grid, "D", ctx->player->pos))
		mlx_string_put(ctx->mlx, ctx->win,
			WIN_W / 2 - 150, WIN_H / 2 + 300, (mlx_color){
			.rgba = 0xA00000FF}, "E: Open door");
	if (get_near_elmt(ctx->map->grid, "O", ctx->player->pos))
		mlx_string_put(ctx->mlx, ctx->win,
			WIN_W / 2 - 150, WIN_H / 2 + 300, (mlx_color){
			.rgba = 0xA00000FF}, "E: Close door");
}

static int	as_moved(t_player *player)
{
	return (
		player->movement[0] || player->movement[1] || player->movement[2]
		|| player->movement[3] || player->rotate[0] || player->rotate[1]
	);
}

static void	display_hud(t_ctx *ctx)
{
	char	*fps;

	display_map(ctx);
	display_rec(ctx);
	if (ctx->frame_time > 0)
	{
		fps = ft_itoa(1000 / ctx->frame_time);
		mlx_string_put(ctx->mlx, ctx->win, 20, 35,
			(mlx_color){.rgba = 0xA10000ff}, fps);
		free(fps);
	}
}

void	update(void *ptr)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ptr;
	if (ctx->player->is_dead)
	{
		mlx_clear_window(ctx->mlx, ctx->win, (mlx_color){
			.rgba=0x000000ff
		});
		mlx_set_font_scale(ctx->mlx, "default", 30);
		mlx_string_put(
			ctx->mlx, ctx->win, WIN_W / 2 - 200, WIN_H / 2 - 200,
			(mlx_color){.rgba = 0xff0000ff}, "You'r dead !"
		);
		return ;
	}
	refresh_frame_time(ctx);
	player_mouse_rotate(ctx);
	player_move(ctx);
	player_rotate(ctx);
	ennemy_move(ctx);
	ctx->player->as_moved = ctx->player->as_moved || as_moved(ctx->player);
	if (ctx->player->as_moved)
		raycaster(ctx->lod_value, ctx);
	else
		raycaster(1, ctx);
	mlx_clear_window(ctx->mlx, ctx->win, (mlx_color){.rgba = 0});
	mlx_put_image_to_window(ctx->mlx, ctx->win, ctx->render, 0, 0);
	display_hud(ctx);
	render_door_text(ctx);
}
