#include "ctx.h"
#include "map.h"
#include "mlx.h"
#include "mlx_extended.h"
#include "render.h"
#include "libft.h"
#include "math.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Init all the value ofa ray based 
 * on it's number (screen x) and player datas
 *
 * @param ray ray to init
 * @param raynumber x that the ray represent on the screen
 * @param ctx global context of cub3d
 */
void	set_ray_val(t_ray *ray, int raynumber, t_ctx *ctx)
{
	ray->cam_x = 2.0 * raynumber / WIN_W - 1;
	ray->ray_dir[X] = ctx->player->dir_vec[X]
		+ ctx->player->plane[X] * ray->cam_x;
	ray->ray_dir[Y] = ctx->player->dir_vec[Y]
		+ ctx->player->plane[Y] * ray->cam_x;
	ray->delta[X] = fabs(1 / (ray->ray_dir[X] + (ray->ray_dir[X] == 0) * 1e30));
	ray->delta[Y] = fabs(1 / (ray->ray_dir[Y] + (ray->ray_dir[Y] == 0) * 1e30));
	ray->step[X] = (ray->ray_dir[X] < 0) * -2 + 1;
	ray->step[Y] = (ray->ray_dir[Y] < 0) * -2 + 1;
	ray->map[X] = (int)ctx->player->pos[X];
	ray->map[Y] = (int)ctx->player->pos[Y];
	if (ray->ray_dir[X] < 0)
		ray->side_dist[X] = (ctx->player->pos[X] - ray->map[X]) * ray->delta[X];
	else
		ray->side_dist[X] = (ray->map[X] + 1 - ctx->player->pos[X])
			* ray->delta[X];
	if (ray->ray_dir[Y] < 0)
		ray->side_dist[Y] = (ctx->player->pos[Y] - ray->map[Y])
			* ray->delta[Y];
	else
		ray->side_dist[Y] = (ray->map[Y] + 1 - ctx->player->pos[Y])
			* ray->delta[Y];
}

/**
 * @brief Make the ray move forward until it hit a wall
 *
 * @param ray all the ray data (already init)
 * @param ctx global context of cub3d
 */
void	hit_loop(t_ray *ray, t_ctx *ctx)
{
	const char	*walls_char = "1D";

	while (!ray->hit)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta[X];
			ray->map[X] += ray->step[X];
			ray->side_hit = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta[Y];
			ray->map[Y] += ray->step[Y];
			ray->side_hit = 1;
		}
		if (ft_strchr(walls_char, ctx->map->grid[ray->map[Y]][ray->map[X]]))
			ray->hit = 1;
	}
	if (ray->side_hit == 0)
		ray->perp_dist = ray->side_dist[X] - ray->delta[X];
	else
		ray->perp_dist = ray->side_dist[Y] - ray->delta[Y];
}


/**
 * @brief Calculate the position of all pixel of the screen and put them
 * into the rneder image
 *
 * @param ctx global context of cub3d
 */
void	raycaster(int lod, t_ctx *ctx)
{
	static mlx_color	pixels[WIN_H * WIN_W];
	size_t				raynumber;
	t_ray				ray;

	raynumber = 0;
	while (raynumber < WIN_W)
	{
		ft_bzero(&ray, sizeof(t_ray));
		set_ray_val(&ray, raynumber, ctx);
		hit_loop(&ray, ctx);
		put_vert_pixels(&ray, raynumber, pixels, ctx);
		raynumber += lod;
	}
	mlx_set_image_region(ctx->mlx, ctx->render, 0, 0, WIN_W, WIN_H, pixels);
}
