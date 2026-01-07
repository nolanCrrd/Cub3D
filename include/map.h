#ifndef MAP_H
# define MAP_H
# include "mlx/

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
	mlx_image	*no
}	t_texture;

typedef struct s_map
{

	char	**grid;
}	t_map;

#endif