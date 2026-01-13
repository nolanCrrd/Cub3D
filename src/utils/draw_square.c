#include "ctx.h"
#include "mlx.h"

void	draw_square(t_ctx *ctx, int *pos, int size, mlx_color color)
{
	int	current_pos[2];

	current_pos[Y] = pos[Y];
	while (current_pos[Y] < pos[Y] + size)
	{
		current_pos[X] = pos[X];
		while (current_pos[X] < pos[X] + size)
		{
			mlx_pixel_put(ctx->mlx, ctx->win, current_pos[X], current_pos[Y], color);
			current_pos[X]++;
		}
		current_pos[Y]++;
	}
}