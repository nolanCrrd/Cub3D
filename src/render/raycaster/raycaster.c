#include "ctx.h"
#include "mlx.h"
#include "mlx_extended.h"
#include "render.h"
#include "libft.h"
#include "math.h"
#include <stddef.h>
#include <stdio.h>

void	set_ray_val(t_ray *ray, int raynumber, t_ctx *ctx)
{
	ray->cam_x = 2.0 * raynumber / WIN_W - 1;
	ray->ray_dir[X] = ctx->player->dir_vec[X] + ctx->player->plane[X] * ray->cam_x;
	ray->ray_dir[Y] = ctx->player->dir_vec[Y] + ctx->player->plane[Y] * ray->cam_x;
	ray->delta[X] = fabs(1 / (ray->ray_dir[X] + (ray->ray_dir[X] == 0) * 1e30));
	ray->delta[Y] = fabs(1 / (ray->ray_dir[Y] + (ray->ray_dir[Y] == 0) * 1e30));
	ray->step[X] = (ray->ray_dir[X] < 0) * -2 + 1;
	ray->step[Y] = (ray->ray_dir[Y] < 0) * -2 + 1;
	ray->map[X] = (int)ctx->player->pos[X];
	ray->map[Y] = (int)ctx->player->pos[Y];
	if (ray->ray_dir[X] < 0)
		ray->side_dist[X] = (ctx->player->pos[X] - ray->map[X]) * ray->delta[X];
	else
		ray->side_dist[X] = (ray->map[X] + 1 - ctx->player->pos[X]) * ray->delta[X];
	if (ray->ray_dir[Y] < 0)
		ray->side_dist[Y] = (ctx->player->pos[Y] - ray->map[Y]) * ray->delta[Y];
	else
		ray->side_dist[Y] = (ray->map[Y] + 1 - ctx->player->pos[Y]) * ray->delta[Y];
}

void	hit_loop(t_ray *ray, t_ctx *ctx)
{
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
		if (ctx->map->grid[ray->map[Y]][ray->map[X]] == '1')
			ray->hit = 1;
	}
	if (ray->side_hit == 0)
		ray->perp_dist = ray->side_dist[X] - ray->delta[X];
	else
		ray->perp_dist = ray->side_dist[Y] - ray->delta[Y];
}

void	draw_ctx_image(t_ray *ray, int x, t_ctx *ctx)
{
	int	line_height;
	int	start;

	// TODO : Comprendre pk ces valeur (hauteur joueur)
	line_height = (int)(WIN_H / ray->perp_dist);
	start = -line_height / 2 + WIN_H / 2;

	if (start < 0)
		start = 0;
	if (line_height >= WIN_H)
		line_height = WIN_H;
	// test
	mlx_color	*color = malloc(sizeof(mlx_color) * line_height);
	for (int i = 0; i < line_height; i++)
	{
		if (ray->side_hit == 0)
			color[i].rgba = 0x7CFC00FF;
		if (ray->side_hit == 1)
			color[i].rgba = 0xFF0000FF;
	}
	mlx_set_image_region(ctx->mlx, ctx->render, x, start, 1, line_height, color);
	free(color);
}

void	raycaster(t_ctx *ctx)
{
	size_t	raynumber;
	t_ray	ray;
	
	raynumber = 0;
	static mlx_color color[WIN_H * WIN_W]; // Tu malloc TOUTE l'image
	for (int i = 0; i < WIN_H * WIN_W; i++)
		color[i].rgba = 0x000000FF; // Tu remplis que WIN_H pixels alors que t'as WIN_H * WIN_W !
	mlx_set_image_region(ctx->mlx, ctx->render, 0, 0, WIN_W, WIN_H, color);
	while (raynumber < WIN_W)
	{
		ft_bzero(&ray, sizeof(t_ray));
		set_ray_val(&ray, raynumber, ctx);
		hit_loop(&ray, ctx);
		draw_ctx_image(&ray, raynumber, ctx);
		raynumber++;
	}
}
