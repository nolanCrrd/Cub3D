/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:05:47 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 11:05:50 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "ennemy.h"
#include "ft_printf.h"
#include "libft.h"
#include "map.h"
#include "mlx.h"
#include "render.h"
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void	destroy_rec(t_ctx *ctx)
{
	if (!ctx->rec)
		return ;
	mlx_destroy_image(ctx->mlx, ctx->rec[0]);
	mlx_destroy_image(ctx->mlx, ctx->rec[1]);
	mlx_destroy_image(ctx->mlx, ctx->rec[2]);
	free(ctx->rec);
	ctx->rec = NULL;
}

void	destroy_textures(t_textures **textures, t_ctx *ctx)
{
	if ((*textures)->north && (*textures)->north->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->north->texture);
	free((*textures)->north);
	if ((*textures)->south && (*textures)->south->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->south->texture);
	free((*textures)->south);
	if ((*textures)->east && (*textures)->east->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->east->texture);
	free((*textures)->east);
	if ((*textures)->west && (*textures)->west->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->west->texture);
	free((*textures)->west);
	if ((*textures)->ceiling_tex && (*textures)->ceiling_tex->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->ceiling_tex->texture);
	free((*textures)->ceiling_tex);
	if ((*textures)->floor_tex && (*textures)->floor_tex->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->floor_tex->texture);
	free((*textures)->floor_tex);
	if ((*textures)->door && (*textures)->door->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->door->texture);
	free((*textures)->door);
	if ((*textures)->ennemy && (*textures)->ennemy->texture)
		mlx_destroy_image(ctx->mlx, (*textures)->ennemy->texture);
	free((*textures)->ennemy);
	free((*textures)->ceiling);
	free((*textures)->floor);
	free(*textures);
	*textures = NULL;
}

void	destroy_map(t_map **map)
{
	size_t	current_y;

	current_y = 0;
	if ((*map)->grid)
	{
		while (current_y < (*map)->size_y)
			free((*map)->grid[current_y++]);
		free((*map)->grid);
	}
	free(*map);
	*map = NULL;
}

void	destroy_ctx(t_ctx **ctx)
{
	if ((*ctx)->map)
		destroy_map(&(*ctx)->map);
	if ((*ctx)->render)
		mlx_destroy_image((*ctx)->mlx, (*ctx)->render);
	if ((*ctx)->win)
		mlx_destroy_window((*ctx)->mlx, (*ctx)->win);
	if ((*ctx)->textures)
		destroy_textures(&(*ctx)->textures, *ctx);
	free((*ctx)->player);
	free((*ctx)->ennemy);
	destroy_rec(*ctx);
	mlx_destroy_context((*ctx)->mlx);
	pthread_mutex_destroy(&(*ctx)->thread_working[0]);
	pthread_mutex_destroy(&(*ctx)->thread_working[1]);
	pthread_mutex_destroy(&(*ctx)->thread_working[2]);
	pthread_mutex_destroy(&(*ctx)->thread_working[3]);
	free((*ctx));
	*ctx = NULL;
}

static void	init_threads_infos(t_ctx *ctx)
{
	static mlx_color	pixels[WIN_W * WIN_H];
	static double		z_buffer[WIN_W];
	int					i;

	i = 0;
	while (i < 4)
	{
		ctx->thread_info[i].pixels = pixels;
		ctx->thread_info[i].z_buffer = z_buffer;
		ctx->thread_info[i].x_start = WIN_W / 4 * i;
		ctx->thread_info[i].x_end = WIN_W / 4 * (i + 1);
		ctx->thread_info[i].x_len = ctx->thread_info[i].x_end - ctx->thread_info[i].x_start;
		ctx->thread_info[i].thread_number = i + 1;
		pthread_mutex_init(&ctx->thread_working[i], NULL);
		i++;
	}
}

t_ctx	*init_ctx(char *file_path)
{
	t_ctx	*ctx;

	ctx = ft_calloc(1, sizeof(t_ctx));
	if (!ctx)
	{
		ft_dprintf(2, "Error\nUnable to init ctx\n");
		return (NULL);
	}
	ctx->map = ft_calloc(1, sizeof(t_map));
	ctx->player = ft_calloc(1, sizeof(t_player));
	ctx->ennemy = ft_calloc(1, sizeof(t_ennemy));
	if (!ctx->map || !ctx->player || !ctx->ennemy)
	{
		ft_dprintf(2, "Error\nUnable to init ctx\n");
		free(ctx->map);
		free(ctx->player);
		free(ctx);
		return (NULL);
	}
	ctx->map->file_path = file_path;
	init_threads_infos(ctx);
	ctx->mlx = mlx_init();
	ctx->lod_value = 4;
	return (ctx);
}
