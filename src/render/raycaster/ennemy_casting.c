#include "ctx.h"
#include "ennemy.h"
#include "mlx.h"
#include "render.h"
#include <stdlib.h>

void	ennemy_casting(double *z_buffer, int lod, mlx_color *pixels, t_ctx *ctx)
{
	double		sprite[2];
	double		transform[2];
	double		inv_det;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			draw_y[3];
	int			draw_x[3];
	int			tex[2];
	int			d;
	int			lod_counter;
	int			floor_y;
	mlx_color	tmp;

	sprite[X] = ctx->ennemy->pos[X] - ctx->player->pos[X];
	sprite[Y] = ctx->ennemy->pos[Y] - ctx->player->pos[Y];
	inv_det = 1 / (ctx->player->plane[X] * ctx->player->dir_vec[Y] - ctx->player->dir_vec[X] * ctx->player->plane[Y]);
	transform[X] = inv_det * (ctx->player->dir_vec[Y] * sprite[X] - ctx->player->dir_vec[X] * sprite[Y]);
	transform[Y] = inv_det * (-ctx->player->plane[Y] * sprite[X] + ctx->player->plane[X] * sprite[Y]);
	sprite_screen_x = (WIN_W >> 1) * (1 + transform[X] / transform[Y]);
	
	sprite_width = abs((int)(WIN_H / (transform[Y]) * E_SCALE));
	if (sprite_screen_x < 0 - (sprite_width >> 1) || sprite_screen_x > WIN_W + (sprite_width >> 1))
		return ;

	floor_y = (WIN_H >> 1) + (WIN_H / transform[Y]) * 0.5;
	draw_x[0] = (-sprite_width >> 1) + sprite_screen_x;
	draw_x[1] = (sprite_width >> 1) + sprite_screen_x;

	sprite_height = abs((int)(WIN_H / transform[Y] * E_SCALE));
	draw_y[0] = floor_y - sprite_height;
	draw_y[1] = floor_y;

	draw_x[2] = draw_x[0];
	while (draw_x[2] < draw_x[1])
	{
		tex[X] = (int)(
			256 * (draw_x[2] - draw_x[0]) * ctx->map->textures->ennemy->width
			/ sprite_width) >> 8;
		if(transform[Y] > 0 && draw_x[2] > 0 && draw_x[2] < WIN_W && transform[Y] < z_buffer[draw_x[2]])
		{
			draw_y[2] = draw_y[0];
			while (draw_y[2] < draw_y[1])
			{
				d = draw_y[2] - (draw_y[0]);
				tex[Y] = d * ctx->map->textures->ennemy->height / sprite_height;
				lod_counter = 0;
				tmp = (
					mlx_get_image_pixel(ctx->mlx, ctx->map->textures->ennemy->texture, tex[X], tex[Y])
				);
				while (lod_counter < lod) 
				{
					if (tmp.rgba != 0x000000FF && draw_y[2] * WIN_W + draw_x[2] + lod_counter < WIN_W * WIN_H
						&& draw_y[2] * WIN_W + draw_x[2] + lod_counter)
						pixels[draw_y[2] * WIN_W + draw_x[2] + lod_counter].rgba = tmp.rgba;
					lod_counter++;
				}
				draw_y[2]++;
			}
		}
		draw_x[2] += lod;
	}
}
