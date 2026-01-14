#include "ctx.h"
#include "mlx.h"
#include "render.h"
#include <math.h>

/**
 * @brief Put all the pixel of the floor and the celling into pixels array
 *
 * @param ray 
 * @param pixels Array of mlx_color (WIN_W x WIN_H)
 * @param ctx 
 */
void	put_f_c_pixels(t_ray *ray, int lod, mlx_color *pixels, t_ctx *ctx)
{
	float	floor_step[2];
	float	floor[2];
	float	posZ;
	float	raw_distance;
	int		cell[2];
	int		current[2];
	int		floor_tex[2];
	int		ceil_tex[2];
	int		p;
	int		i;

	current[Y] = WIN_H * 0.5 + 1;
	ray->ray_dir0[X] = ctx->player->dir_vec[X] - ctx->player->plane[X];
	ray->ray_dir0[Y] = ctx->player->dir_vec[Y] - ctx->player->plane[Y];
	ray->ray_dir1[X] = ctx->player->dir_vec[X] + ctx->player->plane[X];
	ray->ray_dir1[Y] = ctx->player->dir_vec[Y] + ctx->player->plane[Y];
	posZ = 0.5 * WIN_H;
	while (current[Y] < WIN_H)
	{
		p = current[Y] - WIN_H * 0.5;
		raw_distance = posZ / p;
		floor_step[X] = raw_distance * (ray->ray_dir1[X] - ray->ray_dir0[X]) / WIN_W;
		floor_step[Y] = raw_distance * (ray->ray_dir1[Y] - ray->ray_dir0[Y]) / WIN_W;
		floor[X] = ctx->player->pos[X] + raw_distance * ray->ray_dir0[X];
		floor[Y] = ctx->player->pos[Y] + raw_distance * ray->ray_dir0[Y];
		current[X] = 0;
		while (current[X] < WIN_W)
		{
			cell[X] = floor[X];
			cell[Y] = floor[Y];
			floor_tex[X] = fmin((ctx->map->textures->floor_tex->width * (floor[X] - cell[X])), (ctx->map->textures->floor_tex->width - 1));
			floor_tex[Y] = fmin((ctx->map->textures->floor_tex->height * (floor[Y] - cell[Y]))
				,(ctx->map->textures->floor_tex->height - 1));
			ceil_tex[X] = fmin((ctx->map->textures->ceiling_tex->width * (floor[X] - cell[X])), (ctx->map->textures->ceiling_tex->width - 1));
			ceil_tex[Y] = fmin((ctx->map->textures->ceiling_tex->height * (floor[Y] - cell[Y]))
				,(ctx->map->textures->ceiling_tex->height - 1));
			floor[X] += floor_step[X];
			floor[Y] += floor_step[Y];
			i = 0;
			while (i < lod)
			{
				if (WIN_W * (current[Y] + i) + current[X] <= WIN_H * WIN_W)
					pixels[WIN_W * (current[Y] + i) + current[X]] = mlx_get_image_pixel(ctx->mlx, 
						ctx->map->textures->floor_tex->texture, floor_tex[X], floor_tex[Y]);
				if (WIN_W * (WIN_H - current[Y] - 1 + i) + current[X] <= WIN_H * WIN_W)
					pixels[WIN_W * (WIN_H - current[Y] - 1 + i) + current[X]] = mlx_get_image_pixel(ctx->mlx, 
						ctx->map->textures->ceiling_tex->texture, ceil_tex[X], ceil_tex[Y]);
				i++;
			}
			current[X]++;
		}
		current[Y] += lod;
	}
}
