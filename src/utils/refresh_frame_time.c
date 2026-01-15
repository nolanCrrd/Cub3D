/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_frame_time.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:05:42 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 11:05:50 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>
#include "utils.h"

/**
 * @brief Refresh frames data in global context
 *
 * @param ctx 
 */
void	refresh_frame_time(t_ctx *ctx)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ctx->old_frame = ctx->frame;
	ctx->frame = tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
	ctx->frame_time = ctx->frame - ctx->old_frame;
}
