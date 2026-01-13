#include "render.h"
#include "math.h"
#include <stdio.h>

static t_texture	*get_correct_texture(t_ray *ray, t_ctx *ctx)
{
	if (ctx->map->grid[ray->map[Y]][ray->map[X]] == 'D')
		return (ctx->map->textures->door);
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

void	put_vert_pixels(t_ray *ray, int raynumber, mlx_color *pixels, t_ctx *ctx)
{
	t_texture			*texture;
	double				wall_x;
	int					tex[2];
	int					line_height;
	int					start;
	double				step_y;
	double				tex_pos;
	int					draw_y;

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
	start = start * (start >= 0);
	draw_y = start;
	if (line_height > WIN_H)
		line_height = WIN_H;
	while (draw_y < start + line_height)
	{
		tex[Y] = fmin((int)tex_pos, texture->height - 1);
		tex_pos += step_y;
		pixels[draw_y * WIN_W + raynumber] = mlx_get_image_pixel(ctx->mlx, texture->texture, tex[X], tex[Y]);
		if (ray->side_hit == 1)
		{
			pixels[draw_y * WIN_W + raynumber].r *= 0.8;
			pixels[draw_y * WIN_W + raynumber].g *= 0.8;
			pixels[draw_y * WIN_W + raynumber].b *= 0.8;
		}
		draw_y++;
	}
}
