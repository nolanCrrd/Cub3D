#ifndef CTX_H
# define CTX_H
#include "mlx.h"
# include "map.h"
# include "player.h"

typedef struct s_ctx
{
	mlx_context	mlx;
	mlx_window	win;
	mlx_image	render;
	t_player	*player;
	t_map		*map;
	double		old_frame;
	double		frame;
	double		frame_time;
}	t_ctx;

t_ctx	*init_ctx(char *file_path);
void	destroy_ctx(t_ctx **ctx);

#endif
