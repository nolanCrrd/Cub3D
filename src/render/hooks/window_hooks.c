#include "ctx.h"
#include "render.h"

/**
 * @brief Listen to window close event
 *
 * @param event 
 * @param ptr global cub3d context
 */
void	close_hook(int event, void *ptr)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ptr;
	if (event == 0)
		mlx_loop_end(ctx->mlx);
}
