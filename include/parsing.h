/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:06:58 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 13:07:05 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "ctx.h"
# include "map.h"

t_ctx		*parse(char *file_path);
int			check_file(t_map *map);
int			init_map(int fd, t_map *map);
int			init_textures(int fd, t_ctx *ctx);
int			init_player(t_map *map, t_player *player);
int			is_valid_map(t_map *map);
int			is_valid_rgb(char *color);
t_texture	*get_texture(char *path, mlx_context mlx);

#endif
