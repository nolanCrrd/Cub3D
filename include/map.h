#ifndef MAP_H
# define MAP_H
# include <stddef.h>
# include "mlx.h"

#define	X 0
#define Y 1

typedef enum e_map_object
{
	AIR,
	WALL,
	NORTH,
	SOUTH,
	EAST,
	WEST
}	s_map_object;

typedef struct s_texture
{
	mlx_image	texture;
	int			height;
	int			width;
}	t_texture;

typedef struct s_textures
{
	t_texture	*north;
	t_texture	*west;
	t_texture	*south;
	t_texture	*east;
	t_texture	*door;
	t_texture	*ceiling_tex;
	t_texture	*floor_tex;
	mlx_color	*floor;
	mlx_color	*ceiling;		
}	t_textures;

typedef struct s_map
{
	char		*file_path;
	t_textures	*textures;
	char		**grid;
	size_t		size_x;
	size_t		size_y;
}	t_map;
void	show_map(t_map *map);

#endif
