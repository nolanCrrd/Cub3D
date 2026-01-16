/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:06:54 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 13:07:05 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

#include "ennemy.h"
# include "mlx.h"
# include "map.h"
# include "player.h"
#include <bits/pthreadtypes.h>

typedef struct	s_raycaster_thread
{
	mlx_color	*pixels;
	double		*z_buffer;
	int			x_start;
	int			x_end;
	int			x_len;
	int			thread_number;
}	t_raycaster_thread;

typedef struct s_ctx
{
	mlx_context	mlx;
	mlx_window	win;
	mlx_image	render;
	t_player	*player;
	t_ennemy	*ennemy;
	t_map		*map;
	double		old_frame;
	double		frame;
	double		frame_time;
	int			lod_value;
	mlx_image	*rec;
	t_raycaster_thread	thread_info[4];
	pthread_mutex_t		thread_working[4];

}	t_ctx;

t_ctx	*init_ctx(char *file_path);
void	destroy_ctx(t_ctx **ctx);

#endif
