#ifndef PARSING_H
# define PARSING_H
# include "map.h"

t_map	*parse(char *file_path);
int		check_file(t_map *map);
int		init_map(t_map *map);

#endif