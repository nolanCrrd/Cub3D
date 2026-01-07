#ifndef MAP_H
# define MAP_H
# include <stddef.h>
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
	char		*file_path;
	t_textures	*textures;
	char		**grid;
	size_t		size_x;
	size_t		size_y;
}	t_map;

#endif
