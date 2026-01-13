/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:08:35 by ehode             #+#    #+#             */
/*   Updated: 2026/01/13 14:19:27 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ctx.h"
#include "render.h"
#include "utils.h"

static void	draw_player(t_ctx *ctx)
{
	int		tmp_pos[2];

	tmp_pos[X] = MAP_X + (10 * MAP_SIZE);
	tmp_pos[Y] = MAP_Y + (10 * MAP_SIZE);
	draw_square(ctx, tmp_pos, 10, (mlx_color){.rgba = 0x0066b1FF});
}

static void	draw_wall(t_ctx *ctx)
{
	int		current_offset[2];
	int		tmp_pos[2];
	char	tile;

	current_offset[Y] = -MAP_SIZE;
	while (current_offset[Y] < MAP_SIZE)
	{
		current_offset[X] = -MAP_SIZE;
		while (current_offset[X] < MAP_SIZE)
		{
			tile = get_tile(ctx->map, current_offset[X] + ctx->player->pos[X],
					current_offset[Y] + ctx->player->pos[Y]);
			tmp_pos[X] = MAP_X + (10 * (current_offset[X] + MAP_SIZE));
			tmp_pos[Y] = MAP_Y + (10 * (current_offset[Y] + MAP_SIZE));
			if (tile == '1')
				draw_square(ctx, tmp_pos, 10,
					(mlx_color){.r = 0xFF, .g = 0xFF, .b = 0x00, .a = 0xFF});
			else if (tile == ' ')
				draw_square(ctx, tmp_pos, 10,
					(mlx_color){.r = 0xFF, .g = 0xFF, .b = 0x00, .a = 0xC0});
			current_offset[X]++;
		}
		current_offset[Y]++;
	}
}

static void	draw_background(t_ctx *ctx)
{
	int	tmp_pos[2];
	int	current_offset[2];
	int	distance;

	current_offset[Y] = -MAP_SIZE * 10;
	while (current_offset[Y] <= MAP_SIZE * 10)
	{
		current_offset[X] = -MAP_SIZE * 10;
		while (current_offset[X] <= MAP_SIZE * 10)
		{
			tmp_pos[X] = MAP_X + (current_offset[X] + MAP_SIZE * 10);
			tmp_pos[Y] = MAP_Y + (current_offset[Y] + MAP_SIZE * 10);
			distance = get_distance(0, current_offset[X], 0, current_offset[Y]);
			if (distance < MAP_SIZE * 10)
				draw_square(ctx, tmp_pos, 1,
					(mlx_color){.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xAA});
			current_offset[X]++;
		}
		current_offset[Y]++;
	}
}

static void	draw_out_background(t_ctx *ctx)
{
	int	tmp_pos[2];
	int	current_offset[2];
	int	distance;

	current_offset[Y] = -MAP_SIZE * 10;
	while (current_offset[Y] <= MAP_SIZE * 10)
	{
		current_offset[X] = -MAP_SIZE * 10;
		while (current_offset[X] <= MAP_SIZE * 10)
		{
			tmp_pos[X] = MAP_X + (current_offset[X] + MAP_SIZE * 10);
			tmp_pos[Y] = MAP_Y + (current_offset[Y] + MAP_SIZE * 10);
			distance = get_distance(0, current_offset[X], 0, current_offset[Y]);
			if (distance > MAP_SIZE * 10)
				draw_square(ctx, tmp_pos, 1, (mlx_color){.a = 0x00});
			current_offset[X]++;
		}
		current_offset[Y]++;
	}
}

void	display_map(t_ctx *ctx)
{
	draw_background(ctx);
	draw_wall(ctx);
	draw_player(ctx);
	draw_out_background(ctx);
}
