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

typedef struct s_textures
{
	mlx_image	north;
	mlx_image	south;
	mlx_image	east;
	mlx_image	west;
	mlx_color	floor;
	mlx_color	ceiling;			
}	t_textures;

typedef struct s_map
{
	t_textures	*textures;
	char		**grid;
}	t_map;

#endif
