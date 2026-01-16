/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:40:36 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/16 15:47:10 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "ennemy.h"
#include "mlx.h"
#include "render.h"
#include <stdlib.h>

static int	ennemy_picker_init(t_ennemy_picker *picker, t_ctx *ctx)
{
	picker->sprite[X] = ctx->ennemy->pos[X] - ctx->player->pos[X];
	picker->sprite[Y] = ctx->ennemy->pos[Y] - ctx->player->pos[Y];
	picker->inv_det = 1 / (ctx->player->plane[X] * ctx->player->dir_vec[Y]
			- ctx->player->dir_vec[X] * ctx->player->plane[Y]);
	picker->transform[X] = picker->inv_det * (ctx->player->dir_vec[Y]
			* picker->sprite[X] - ctx->player->dir_vec[X] * picker->sprite[Y]);
	picker->transform[Y] = picker->inv_det * (-ctx->player->plane[Y]
			* picker->sprite[X] + ctx->player->plane[X] * picker->sprite[Y]);
	picker->sprite_screen_x = (WIN_W >> 1) * (1 + picker->transform[X]
			/ picker->transform[Y]);
	picker->sprite_width = abs((int)(WIN_H / (picker->transform[Y]) * E_SCALE));
	if (picker->sprite_screen_x < 0 - (picker->sprite_width >> 1)
		|| picker->sprite_screen_x > WIN_W + (picker->sprite_width >> 1))
		return (1);
	picker->floor_y = (WIN_H >> 1) + (WIN_H / picker->transform[Y]) * 0.5;
	picker->draw_x[0] = (-picker->sprite_width >> 1) + picker->sprite_screen_x;
	picker->draw_x[1] = (picker->sprite_width >> 1) + picker->sprite_screen_x;
	picker->sprite_height = abs((int)(WIN_H / picker->transform[Y] * E_SCALE));
	picker->draw_y[0] = picker->floor_y - picker->sprite_height;
	picker->draw_y[1] = picker->floor_y;
	picker->draw_x[2] = picker->draw_x[0];
	return (0);
}

static void	lod_loop(int lod, t_ennemy_picker *picker,
	mlx_color *pixels, t_ctx *ctx)
{
	mlx_color	tmp;
	int			lod_counter;

	tmp = (mlx_get_image_pixel(ctx->mlx, ctx->textures->ennemy
				->texture, picker->tex[X], picker->tex[Y]));
	lod_counter = 0;
	while (lod_counter < lod)
	{
		if (tmp.rgba != 0x000000FF && picker->draw_y[2] * WIN_W
			+ picker->draw_x[2] + lod_counter < WIN_W * WIN_H
			&& picker->draw_y[2] * WIN_W + picker->draw_x[2]
			+ lod_counter)
			pixels[picker->draw_y[2] * WIN_W + picker->draw_x[2]
				+ lod_counter].rgba = tmp.rgba;
		lod_counter++;
	}
}

void	ennemy_casting(double *z_buffer, int lod, mlx_color *pixels, t_ctx *ctx)
{
	t_ennemy_picker	picker;

	if (ennemy_picker_init(&picker, ctx))
		return ;
	while (picker.draw_x[2] < picker.draw_x[1])
	{
		picker.tex[X] = (int)(
				256 * (picker.draw_x[2] - picker.draw_x[0])
				* ctx->textures->ennemy->width / picker.sprite_width) >> 8;
		if (picker.transform[Y] > 0 && picker.draw_x[2] > 0 && picker.draw_x[2]
			< WIN_W && picker.transform[Y] < z_buffer[picker.draw_x[2]])
		{
			picker.draw_y[2] = picker.draw_y[0];
			while (picker.draw_y[2] < picker.draw_y[1])
			{
				picker.d = picker.draw_y[2] - (picker.draw_y[0]);
				picker.tex[Y] = picker.d * ctx->textures->ennemy->height
					/ picker.sprite_height;
				lod_loop(lod, &picker, pixels, ctx);
				picker.draw_y[2]++;
			}
		}
		picker.draw_x[2] += lod;
	}
}
