#include "ctx.h"
#include "render.h"

void	close_hook(int event, void *ptr)
{
	t_ctx *ctx2;

	ctx2 = (t_ctx *)ptr;
	if (event == 0)
		mlx_loop_end(ctx2->mlx);
}
