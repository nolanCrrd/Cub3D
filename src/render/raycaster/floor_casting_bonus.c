#include "ctx.h"
#include "mlx.h"
#include "render.h"
#include <math.h>

static void	init_y_picker(t_floor_picker *picker, t_ray *ray, t_ctx *ctx)
{
	picker->p = picker->current[Y] - WIN_H * 0.5;
	picker->raw_distance = picker->posZ / picker->p;
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

static void	init_x_picker(t_floor_picker *picker, t_ctx *ctx)
{
	picker->cell[X] = picker->floor[X];
	picker->cell[Y] = picker->floor[Y];
	picker->floor_tex[X] = fmin(
			(ctx->map->textures->floor_tex->width * (
					picker->floor[X] - picker->cell[X])), (
				ctx->map->textures->floor_tex->width - 1));
	picker->floor_tex[Y] = fmin(
			(ctx->map->textures->floor_tex->height * (
					picker->floor[Y] - picker->cell[Y])), (
				ctx->map->textures->floor_tex->height - 1));
	picker->ceil_tex[X] = fmin(
			(ctx->map->textures->ceiling_tex->width * (
					picker->floor[X] - picker->cell[X])), (
				ctx->map->textures->ceiling_tex->width - 1));
	picker->ceil_tex[Y] = fmin(
			(ctx->map->textures->ceiling_tex->height * (
					picker->floor[Y] - picker->cell[Y])), (
				ctx->map->textures->ceiling_tex->height - 1));
	picker->floor[X] += picker->floor_step[X];
	picker->floor[Y] += picker->floor_step[Y];
	picker->lod_counter = 0;
}

static void	lod_loop(t_floor_picker *picker, int lod,
	mlx_color *pixels, t_ctx *ctx)
{
	while (picker->lod_counter < lod)
	{
		if (WIN_W * (picker->current[Y] + picker->lod_counter)
			+ picker->current[X] <= WIN_H * WIN_W)
			pixels[WIN_W * (picker->current[Y] + picker->lod_counter)
				+ picker->current[X]] = mlx_get_image_pixel(ctx->mlx,
					ctx->map->textures->floor_tex->texture,
					picker->floor_tex[X], picker->floor_tex[Y]);
		if (WIN_W * (WIN_H - picker->current[Y] - 1 + picker->lod_counter)
			+ picker->current[X] <= WIN_H * WIN_W)
			pixels[WIN_W * (WIN_H - picker->current[Y] - 1
					+ picker->lod_counter) + picker->current[X]]
				= mlx_get_image_pixel(ctx->mlx,
					ctx->map->textures->ceiling_tex->texture,
					picker->ceil_tex[X], picker->ceil_tex[Y]);
		picker->lod_counter++;
	}
}

/**
 * @brief Put all the pixel of the floor and the celling into pixels array
 *
 * @param ray 
 * @param pixels Array of mlx_color (WIN_W x WIN_H)
 * @param ctx 
 */
void	put_f_c_pixels(t_ray *ray, int lod, mlx_color *pixels, t_ctx *ctx)
{
	t_floor_picker	picker;

	picker.current[Y] = WIN_H * 0.5 + 1;
	ray->ray_dir0[X] = ctx->player->dir_vec[X] - ctx->player->plane[X];
	ray->ray_dir0[Y] = ctx->player->dir_vec[Y] - ctx->player->plane[Y];
	ray->ray_dir1[X] = ctx->player->dir_vec[X] + ctx->player->plane[X];
	ray->ray_dir1[Y] = ctx->player->dir_vec[Y] + ctx->player->plane[Y];
	picker.posZ = 0.5 * WIN_H;
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
