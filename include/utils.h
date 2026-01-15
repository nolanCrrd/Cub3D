/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:07:03 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 15:39:51 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "map.h"
# include "ctx.h"

int		is_blank(char *str);
void	remove_spaces(char *s);
char	*skip_empty_lines(int fd);
t_map	*clone_map(t_map *map);
void	refresh_frame_time(t_ctx *ctx);
char	get_tile(t_map *map, size_t x, size_t y);
float	get_distance(float x1, float x2, float y1, float y2);
void	draw_square(t_ctx *ctx, int *pos, int size, mlx_color color);
int		*get_near_elmt(char **grid, char *charset, double *pos);
void	finish_get_next_line(int fd);

#endif
