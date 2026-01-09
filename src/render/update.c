#include "ctx.h"
#include "render.h"
#include "utils.h"

void update(void *ptr)
{
	t_ctx *ctx;

	ctx = (t_ctx *)ptr;
	ctx->old_frame = ctx->frame;
	refresh_frame_time(ctx);
}
