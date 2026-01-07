#ifndef CTX_H
# define CTX_H
# include "map.h"
# include "player.h"

typedef struct s_ctx
{
	t_player	*player;
	t_map		*map;
}	t_ctx;

#endif