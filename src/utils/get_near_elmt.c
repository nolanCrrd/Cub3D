#include "utils.h"
#include "libft.h"

int	*get_near_elmt(char **grid, char *charset, double *pos)
{
	static int	diff[2];

	diff[Y] = -1;
	while (diff[Y] < 2)
	{
		diff[X] = -1;
		while (diff[X] < 2)
		{
			if (ft_strchr(charset, grid[(int)pos[Y] + diff[Y]]
					[(int)pos[X] + diff[X]]))
				return (diff);
			diff[X]++;
		}
		diff[Y]++;
	}
	return (NULL);
}
