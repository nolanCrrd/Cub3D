#ifndef PARSING_H
# define PARSING_H
# include "ctx.h"
# include "map.h"

t_ctx	*parse(char *file_path);
int		check_file(t_map *map);
int		init_map(int fd, t_map *map);
int		init_textures(int fd, t_ctx *ctx);
int		init_player(t_map *map, t_player *player);
int		is_valid_map(t_map *map);
int		is_valid_rgb(char *color);

#endif
