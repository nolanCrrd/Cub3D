#ifndef MAP_H
# define MAP_H
# include "mlx.h"

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
	mlx_color	*floor;
	mlx_color	*ceiling;		
}	t_textures;

typedef struct s_map
{
	t_textures	*textures;
	char		**grid;
	int			size_x;
	int			size_y;
}	t_map;

#endif
