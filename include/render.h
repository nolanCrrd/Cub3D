#ifndef RENDER_H
# define RENDER_H

# define WIN_W 1920
# define WIN_H 1080
# define MAP_SIZE 10
# define MAP_X 50
# define MAP_Y 50

#include "ctx.h"

int	render_cub3d(t_ctx *ctx);
void update(void *ptr);

//hooks
void	close_hook(int event, void *ptr);
void	player_move(t_ctx *ctx);
void	player_rotate(t_ctx *ctx);
void	player_mouse_rotate(t_ctx *ctx);
void	rotate_dir(double *dir, double *plane, double r_speed);
void	all_keydown_hooks(int key, void *ptr);
void	all_keyup_hooks(int key, void *ptr);
void	display_map(t_ctx *ctx);

// raycaster
typedef struct s_ray
{
	double	ray_dir[2];
	double	step[2];
	double	delta[2];
	double	side_dist[2];
	double	perp_dist;
	double	cam_x;
	int		map[2];
	int		hit;
	int		side_hit;
}	t_ray;
void	raycaster(t_ctx *ctx);

#endif
