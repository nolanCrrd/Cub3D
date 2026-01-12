#include "ctx.h"
#include "key.h"
#include "player.h"
#include <endian.h>

static void	player_movement(int key, t_ctx *ctx)
{
	if (key == KEY_W)
		ctx->player->movement[0] = 0;
	if (key == KEY_S)
		ctx->player->movement[1] = 0;
	if (key == KEY_A)
		ctx->player->movement[2] = 0;
	if (key == KEY_D)
		ctx->player->movement[3] = 0;
	if (key == KEY_SHIFT)
		ctx->player->speed = P_M_SPEED;
}

static void	rotate_player(int key, t_ctx *ctx)
{
	if (key == KEY_LEFT)
		ctx->player->rotate[1] = 0;
	if (key == KEY_RIGHT)
		ctx->player->rotate[0] = 0;
}

void	all_keyup_hooks(int key, void *ptr)
{
	t_ctx *ctx;

	ctx = (t_ctx *)ptr;
	player_movement(key, ctx);
	rotate_player(key, ctx);
}
