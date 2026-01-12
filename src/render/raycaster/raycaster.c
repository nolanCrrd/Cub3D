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

t_texture	*get_correct_texture(t_ray *ray, t_ctx *ctx)
{
	if (ray->side_hit == 1)
	{
		if (ray->ray_dir[Y] > 0 && ray->ray_dir[Y] != 1e30)
			return (ctx->map->textures->north);
		return (ctx->map->textures->south);
	}
	if (ray->ray_dir[X] > 0 && ray->ray_dir[X] != 1e30)
		return (ctx->map->textures->west);
	return (ctx->map->textures->east);
}

static void	draw_ctx_image_texture(t_ray *ray, int raynumber, t_ctx *ctx)
{
	t_texture			*texture;
	double				wall_x;
	int					tex[2];
	int					line_height;
	int					start;
	double				step_y;
	double				tex_pos;
	int					draw_y;
	static mlx_color	line_pixels[WIN_H];

	line_height = (int)(WIN_H / ray->perp_dist);
	start = -line_height / 2 + WIN_H / 2;

	texture = get_correct_texture(ray, ctx);
	if (ray->side_hit == 0)
		wall_x = ctx->player->pos[Y] + ray->perp_dist * ray->ray_dir[Y];
	else
		wall_x = ctx->player->pos[X] + ray->perp_dist * ray->ray_dir[X];
	wall_x -= floor(wall_x);

	tex[X] = wall_x * texture->width;
	if ((ray->side_hit == 0 && ray->ray_dir[X] > 0))
		tex[X] = texture->width - tex[X] - 1;
	if ((ray->side_hit == 1 && ray->ray_dir[Y] < 0))
		tex[X] = texture->width - tex[X] - 1;

	step_y = 1.0 * texture->height / line_height;
	tex_pos = ((start >= 0) * start - WIN_H / 2.0 + line_height / 2.0) * step_y;
	draw_y = 0;
	while (draw_y < WIN_H)
	{
		if (draw_y < start)
			line_pixels[draw_y] = (mlx_color){.rgba = ctx->map->textures->ceiling->rgba};
		else if (draw_y < start + line_height)
		{
			tex[Y] = (int)tex_pos & (texture->height - 1);
			tex_pos += step_y;
			line_pixels[draw_y] = mlx_get_image_pixel(ctx->mlx, texture->texture, tex[X], tex[Y]);
			if (ray->side_hit == 1)
			{
				line_pixels[draw_y].r *= 0.8;
				line_pixels[draw_y].g *= 0.8;
				line_pixels[draw_y].b *= 0.8;
			}
		}
		else
			line_pixels[draw_y] = (mlx_color){.rgba = ctx->map->textures->floor->rgba};
		draw_y++;
	}
	mlx_set_image_region(ctx->mlx, ctx->render, raynumber, 0, 1, WIN_H, line_pixels);
}

void	raycaster(t_ctx *ctx)
{
	size_t	raynumber;
	t_ray	ray;
	
	raynumber = 0;
	while (raynumber < WIN_W)
	{
		ft_bzero(&ray, sizeof(t_ray));
		set_ray_val(&ray, raynumber, ctx);
		hit_loop(&ray, ctx);
		draw_ctx_image_texture(&ray, raynumber, ctx);
		raynumber++;
	}
}
