#include "ft_printf.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_ctx	*ctx;

	if (argc != 2)
	{
		ft_dprintf(2, "Usage: %s <*.cub>\n", argv[0]);
		return (2);
	}
	ctx = parse(argv[1]);
	destroy_ctx(&ctx);
	return (0);
}