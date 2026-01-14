/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:08:35 by ehode             #+#    #+#             */
/*   Updated: 2026/01/14 15:20:40 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "ctx.h"
#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"
#include "mlx_extended.h"
#include "render.h"
#include "mlx.h"

void	load_rec(t_ctx *ctx)
{
	const char	*rec_assets[] = {"assets/rec_1.png", "assets/rec_2.png",
		"assets/rec_3.png", NULL};
	int		i;

	ctx->rec = ft_calloc(3, sizeof(mlx_image));
	if (!ctx->rec)
		return ;
	i = 0;
	while (i < 3)
	{
		ctx->rec[i] = mlx_new_image_from_file(ctx->mlx, (char *)rec_assets[i], NULL, NULL);
		if (!ctx->rec[i])
		{
			ft_dprintf(2, "Error\nUnable to load rec assets\n");
			i--;
			while (i > 0)
			{
				mlx_destroy_image(ctx->mlx, ctx->rec[i]);
				i--;
			}
			ctx->rec = NULL;
			break ;
		}
		i++;
	}
}

void	display_rec(t_ctx *ctx)
{
	int	tmp_pos[2];

	tmp_pos[X] = REC_X;
	tmp_pos[Y] = REC_Y;
	if (!ctx->rec)
		return ;
	if ((((size_t)ctx->frame * 10000) / 1000000) % 20 >= 15)
		mlx_put_transformed_image_to_window(ctx->mlx, ctx->win, ctx->rec[0], REC_X + 60, REC_Y + 40, 0.5, 0.5, 0);
	else if ((((size_t)ctx->frame * 10000) / 1000000) % 20 >= 10)
		mlx_put_transformed_image_to_window(ctx->mlx, ctx->win, ctx->rec[1], REC_X + 60, REC_Y + 40, 0.5, 0.5, 0);
	else if ((((size_t)ctx->frame * 10000) / 1000000) % 20 >= 5)
		mlx_put_transformed_image_to_window(ctx->mlx, ctx->win, ctx->rec[2], REC_X + 60, REC_Y + 40, 0.5, 0.5, 0);
	else
		mlx_put_transformed_image_to_window(ctx->mlx, ctx->win, ctx->rec[1], REC_X + 60, REC_Y + 40, 0.5, 0.5, 0);
	mlx_string_put(ctx->mlx, ctx->win, REC_X + 120, REC_Y + 78, (mlx_color){
		.rgba = 0xFFFFFFFF}, "REC");
}
