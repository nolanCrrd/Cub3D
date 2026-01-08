#ifndef UTILS_H
# define UTILS_H
# include "map.h"

int		is_blank(char *str);
void	remove_spaces(char *s);
char	*skip_empty_lines(int fd);
t_map	*clone_map(t_map *map);

#endif
