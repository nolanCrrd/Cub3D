#include "render.h"
#include "math.h"

/**
 * @brief Return the correct texture based on the direction that the wall was hit
 *
 * @param ray
 * @param ctx 
 * @return  structure that contain texture image and it's widht / height
 */
static t_texture	*get_correct_texture(t_ray *ray, t_ctx *ctx)
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

static void	picker_init(t_wall_picker *picker, t_ray *ray, t_ctx *ctx)
{
	picker->line_height = (int)(WIN_H / ray->perp_dist);
	picker->start = -picker->line_height / 2 + WIN_H / 2;
	picker->texture = get_correct_texture(ray, ctx);
	if (ray->side_hit == 0)
		picker->wall_x = ctx->player->pos[Y] + ray->perp_dist * ray->ray_dir[Y];
	else
		picker->wall_x = ctx->player->pos[X] + ray->perp_dist * ray->ray_dir[X];
	picker->wall_x -= floor(picker->wall_x);
	picker->tex[X] = picker->wall_x * picker->texture->width;
	if ((ray->side_hit == 0 && ray->ray_dir[X] < 0))
		picker->tex[X] = picker->texture->width - picker->tex[X] - 1;
	if ((ray->side_hit == 1 && ray->ray_dir[Y] > 0))
		picker->tex[X] = picker->texture->width - picker->tex[X] - 1;
	picker->step_y = 1.0 * picker->texture->height / picker->line_height;
	picker->tex_pos = ((picker->start >= 0) * picker->start - WIN_H
			* 0.5 + picker->line_height * 0.5) * picker->step_y;
	picker->draw_y = 0;
}

static void	darker_color(t_wall_picker picker, t_ray *ray, mlx_color *pixels)
{
	if (ray->side_hit == 1)
	{
		pixels[picker.draw_y * WIN_W + ray->number + picker.lod_counter]
			.r *= 0.8;
		pixels[picker.draw_y * WIN_W + ray->number + picker.lod_counter]
			.g *= 0.8;
		pixels[picker.draw_y * WIN_W + ray->number + picker.lod_counter]
			.b *= 0.8;
	}
}

/**
 * @brief Put the wall pixels into the pixels array
 *
 * @param ray
 * @param raynumber X represented by the ray
 * @param pixels Array WIN_H x WIN_W
 * @param ctx 
 */
void	put_vert_pixels(t_ray *ray, int raynumber,
	mlx_color *pixels, t_ctx *ctx)
{
	t_wall_picker	picker;

	picker_init(&picker, ray, ctx);
	while (picker.draw_y < WIN_H)
	{
		if (picker.draw_y < picker.start)
			pixels[picker.draw_y * WIN_W + raynumber] = (mlx_color){
				.rgba = ctx->map->textures->ceiling->rgba};
		else if (picker.draw_y < picker.start + picker.line_height)
		{
			picker.tex[Y] = fmin((int)picker.tex_pos, picker
					.texture->height - 1);
			picker.tex_pos += picker.step_y;
			pixels[picker.draw_y * WIN_W + raynumber]
				= mlx_get_image_pixel(ctx->mlx, picker
					.texture->texture, picker.tex[X], picker.tex[Y]);
			darker_color(picker, ray, pixels);
		}
		else
			pixels[picker.draw_y * WIN_W + raynumber]
				= (mlx_color){.rgba = ctx->map->textures->floor->rgba};
		picker.draw_y++;
	}
}
