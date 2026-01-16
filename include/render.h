/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:07:01 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 17:38:36 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include "mlx.h"
# define WIN_W 1920
# define WIN_H 1080
# define MAP_SIZE 10
# define MAP_X 150
# define MAP_Y 50
# define REC_X 1500
# define REC_Y 100

# include "ctx.h"

int		render_cub3d(t_ctx *ctx);
void	update(void *ptr);

//hooks
void	close_hook(int event, void *ptr);
void	ennemy_move(t_ctx *ctx);
void	player_move(t_ctx *ctx);
void	player_rotate(t_ctx *ctx);
void	player_mouse_rotate(t_ctx *ctx);
void	rotate_dir(double *dir, double *plane, double r_speed);
void	all_keydown_hooks(int key, void *ptr);
void	all_keyup_hooks(int key, void *ptr);
void	display_map(t_ctx *ctx);
void	display_border(t_ctx *ctx);
void	display_rec(t_ctx *ctx);
void	load_rec(t_ctx *ctx);

// raycaster
typedef struct s_ray
{
	double	ray_dir[2];
	double	ray_dir0[2];
	double	ray_dir1[2];
	double	step[2];
	double	delta[2];
	double	side_dist[2];
	double	perp_dist;
	double	cam_x;
	int		map[2];
	int		hit;
	int		side_hit;
	int		number;
}	t_ray;

typedef struct s_wall_picker
{
	t_texture	*texture;
	double		wall_x;
	int			tex[2];
	int			line_height;
	int			start;
	double		step_y;
	double		tex_pos;
	int			draw_y;
	int			lod_counter;
}	t_wall_picker;

typedef struct s_floor_picker
{
	float	floor_step[2];
	float	floor[2];
	float	pos_z;
	float	raw_distance;
	int		cell[2];
	int		current[2];
	int		floor_tex[2];
	int		ceil_tex[2];
	int		p;
	int		lod_counter;
}	t_floor_picker;

void	raycaster(int lod, t_ctx *ctx);
void	put_f_c_pixels(t_ray *ray, int lod, mlx_color *pixels, t_ctx *ctx);
void	put_vert_pixels(t_ray *ray, int lod, mlx_color *pixels, t_ctx *ctx);
void	ennemy_casting(double *z_buffer, int lod, mlx_color *pixels, t_ctx *ctx);

// multi thread

void	thread_routine1(void *ptr);
void	thread_routine2(void *ptr);
void	thread_routine3(void *ptr);
void	thread_routine4(void *ptr);
void	raycaster_thread(int lod, t_raycaster_thread *thread_info, t_ctx *ctx);
void	ennemy_casting_thread(double *z_buffer, int lod, t_raycaster_thread *thread_info, t_ctx *ctx);
void	put_vert_pixels_thread(t_ray *ray, int lod, t_raycaster_thread *thread_info, t_ctx *ctx);
void	put_f_c_pixels_thread(t_ray *ray, int lod, t_raycaster_thread *thread_info, t_ctx *ctx);

#endif
