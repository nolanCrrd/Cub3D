#include "ft_printf.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_dprintf(2, "Usage: %s <*.cub>\n", argv[0]);
		return (2);
	}
	parse(argv[1]);
	return (0);
}