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

#endif
