/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:08:35 by ehode             #+#    #+#             */
/*   Updated: 2026/01/13 19:03:14 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "ctx.h"
#include "render.h"
#include "utils.h"

static void	draw_circle(t_ctx *ctx, int *pos, int size, mlx_color color)
{
	int	tmp_pos[2];
	int	current_offset[2];
	int	distance;

	current_offset[Y] = -size;
	while (current_offset[Y] <= size)
	{
		current_offset[X] = -size;
		while (current_offset[X] <= size)
		{
			tmp_pos[X] = pos[X] + (current_offset[X] + size);
			tmp_pos[Y] = pos[Y] + (current_offset[Y] + size);
			distance = get_distance(0, current_offset[X], 0, current_offset[Y]);
			if (distance < size)
				mlx_pixel_put(ctx->mlx, ctx->win,
					tmp_pos[X], tmp_pos[Y], color);
			current_offset[X]++;
		}
		current_offset[Y]++;
	}
}

void	display_rec(t_ctx *ctx)
{
	int	tmp_pos[2];

	tmp_pos[X] = REC_X;
	tmp_pos[Y] = REC_Y;
	if ((((size_t)ctx->frame * 1000) / 1000000) % 2 > 0)
		draw_circle(ctx, tmp_pos, 25, (mlx_color){.rgba = 0xFF0000FF});
	else
		draw_circle(ctx, tmp_pos, 25, (mlx_color){.rgba = 0x000000FF});
	mlx_string_put(ctx->mlx, ctx->win, REC_X + 60, REC_Y + 40, (mlx_color){
		.rgba = 0xFFFFFFFF}, "REC");
}
