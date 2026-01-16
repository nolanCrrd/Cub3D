/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:07:00 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 13:07:05 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define P_M_SPEED 1.5
# define P_R_SPEED 2

typedef struct s_player
{
	double	pos[2];
	double	dir_vec[2];
	double	plane[2];
	double	dir_a;
	double	speed;
	int		movement[5];
	int		rotate[2];
	int		mouse_x;
	int		as_moved;
	int		is_dead;
}	t_player;

#endif
