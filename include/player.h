#ifndef PLAYER_H
# define PLAYER_H

# define P_M_SPEED 1.5
# define P_R_SPEED 1.5

typedef struct s_player
{
	double	pos[2];
	double	dir_vec[2];
	double	plane[2];
	double	dir_a;
	double	speed;
	int		movement[5];
	int		rotate[2];
}	t_player;


#endif
