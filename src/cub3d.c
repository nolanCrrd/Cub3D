#include "parsing.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (2);
	parse(argv[1]);
	return (0);
}