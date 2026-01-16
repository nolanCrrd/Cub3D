/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:47:52 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 10:55:37 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	{
		ctx->player->is_dead = 1;
		mlx_loop_end(ctx->mlx);
	}
}
