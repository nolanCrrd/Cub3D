#ifndef RENDER_H
# define RENDER_H

# define WIN_W 1920
# define WIN_H 1080

#include "ctx.h"

int	render_cub3d(t_ctx *ctx);
void update(void *ptr);

//hooks
void	close_hook(int event, void *ptr);
void	all_keyboard_hooks(int key, void *ptr);

#endif
