#ifndef PLAYER_H
# define PLAYER_H

# define PLAYER_BASE_SPEED 10;

#define	X 0;
#define Y 1;

typedef struct s_player
{
	double	pos[2];
	double	direction_vec[2];
	double	direction_angle;
	double	speed;
}	t_player;

#endif
