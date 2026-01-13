/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:08:35 by ehode             #+#    #+#             */
/*   Updated: 2026/01/13 19:00:33 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "ctx.h"
#include "render.h"
#include "utils.h"

static uint8_t	calc_opacity(int distance)
{
	if (distance % 512 > 255)
		return (distance % 512);
	else
		return (0xFF);
}

static void	draw_out_background(t_ctx *ctx)
{
	int	tmp_pos[2];
	int	current_offset[2];
	int	distance;

	current_offset[Y] = -(WIN_H / 2);
	while (current_offset[Y] <= WIN_H / 2)
	{
		current_offset[X] = -(WIN_W / 2);
		while (current_offset[X] <= WIN_W / 2)
		{
			tmp_pos[X] = WIN_W / 2 + current_offset[X];
			tmp_pos[Y] = WIN_H / 2 + current_offset[Y];
			distance = get_distance(0, current_offset[X], 0, current_offset[Y]);
			if (distance > WIN_W / 2)
				draw_square(ctx, tmp_pos, 1,
					(mlx_color){.r = 0, .g = 0, .b = 0,
					.a = calc_opacity(distance)});
			current_offset[X]++;
		}
		current_offset[Y]++;
	}
}

void	display_border(t_ctx *ctx)
{
	draw_out_background(ctx);
}
