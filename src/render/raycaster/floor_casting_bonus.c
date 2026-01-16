/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:55:32 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 10:55:37 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "mlx.h"
#include "render.h"
#include <math.h>

/**
 * @brief Init all the data for Y loop to pick up the correct texture pixel
 *
 * @param picker picker to fill
 * @param ray ray information
 * @param ctx global cub3d context
 */
static void	init_y_picker(t_floor_picker *picker, t_ray *ray, t_ctx *ctx)
{
	picker->p = picker->current[Y] - WIN_H * 0.5;
	picker->raw_distance = picker->pos_z / picker->p;
	picker->floor_step[X] = picker->raw_distance * (
			ray->ray_dir1[X] - ray->ray_dir0[X]) / WIN_W;
	picker->floor_step[Y] = picker->raw_distance * (
			ray->ray_dir1[Y] - ray->ray_dir0[Y]) / WIN_W;
	picker->floor[X] = ctx->player->pos[X]
		+ picker->raw_distance * ray->ray_dir0[X];
	picker->floor[Y] = ctx->player->pos[Y]
		+ picker->raw_distance * ray->ray_dir0[Y];
	picker->current[X] = 0;
}

/**
 * @brief Init all the data of X loop to pick up the correct texture pixel
 *
 * @param picker picker to fill
 * @param ctx global cub3d context
 */
static void	init_x_picker(t_floor_picker *picker, t_ctx *ctx)
{
	picker->cell[X] = picker->floor[X];
	picker->cell[Y] = picker->floor[Y];
	picker->floor_tex[X] = fmin(
			(ctx->textures->floor_tex->width * (
					picker->floor[X] - picker->cell[X])), (
				ctx->textures->floor_tex->width - 1));
	picker->floor_tex[Y] = fmin(
			(ctx->textures->floor_tex->height * (
					picker->floor[Y] - picker->cell[Y])), (
				ctx->textures->floor_tex->height - 1));
	picker->ceil_tex[X] = fmin(
			(ctx->textures->ceiling_tex->width * (
					picker->floor[X] - picker->cell[X])), (
				ctx->textures->ceiling_tex->width - 1));
	picker->ceil_tex[Y] = fmin(
			(ctx->textures->ceiling_tex->height * (
					picker->floor[Y] - picker->cell[Y])), (
				ctx->textures->ceiling_tex->height - 1));
	picker->floor[X] += picker->floor_step[X];
	picker->floor[Y] += picker->floor_step[Y];
	picker->lod_counter = 0;
}

/**
 * @brief Draw multiple time the same pixel based on the LOD level
 *
 * @param picker texture picker data
 * @param lod LOD level (number of simplified pixels)
 * @param pixels array that contain all the screen mlx_color
 * @param ctx global cub3d context
 */
static void	lod_loop(t_floor_picker *picker, int lod,
	mlx_color *pixels, t_ctx *ctx)
{
	mlx_color	tmp;
	mlx_color	tmp2;

	tmp = mlx_get_image_pixel(ctx->mlx,
					ctx->textures->floor_tex->texture,
					picker->floor_tex[X], picker->floor_tex[Y]);
	tmp2 = mlx_get_image_pixel(ctx->mlx,
					ctx->textures->ceiling_tex->texture,
					picker->ceil_tex[X], picker->ceil_tex[Y]);
	while (picker->lod_counter < lod)
	{
		if (WIN_W * (picker->current[Y] + picker->lod_counter)
			+ picker->current[X] < WIN_H * WIN_W)
			pixels[WIN_W * (picker->current[Y] + picker->lod_counter)
				+ picker->current[X]] = tmp;
		if (WIN_W * (WIN_H - picker->current[Y] - 1 + picker->lod_counter)
			+ picker->current[X] < WIN_H * WIN_W)
			pixels[WIN_W * (WIN_H - picker->current[Y] - 1
					+ picker->lod_counter) + picker->current[X]]
				= tmp2;
		picker->lod_counter++;
	}
}

/**
 * @brief Put into the pixel array all the texture of floor and
 * celling with an LOD level
 *
 * @param ray current ray
 * @param lod LOD level (number of simplified pixels)
 * @param pixels pixels array mlx_color of all the screen
 * @param ctx global cub3d context
 */
void	put_f_c_pixels(t_ray *ray, int lod, mlx_color *pixels, t_ctx *ctx)
{
	t_floor_picker	picker;

	picker.current[Y] = WIN_H * 0.5 + 1;
	ray->ray_dir0[X] = ctx->player->dir_vec[X] - ctx->player->plane[X];
	ray->ray_dir0[Y] = ctx->player->dir_vec[Y] - ctx->player->plane[Y];
	ray->ray_dir1[X] = ctx->player->dir_vec[X] + ctx->player->plane[X];
	ray->ray_dir1[Y] = ctx->player->dir_vec[Y] + ctx->player->plane[Y];
	picker.pos_z = 0.5 * WIN_H;
	while (picker.current[Y] < WIN_H)
	{
		init_y_picker(&picker, ray, ctx);
		while (picker.current[X] < WIN_W)
		{
			init_x_picker(&picker, ctx);
			lod_loop(&picker, lod, pixels, ctx);
			picker.current[X]++;
		}
		picker.current[Y] += lod;
	}
}
