#include "libft.h"
#include "utils.h"

/**
 * @brief Skip all the line int he fd that contain only whitespaces
 *
 * @param fd
 * @return 
 */
static char	*skip_empty_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && is_blank(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}
