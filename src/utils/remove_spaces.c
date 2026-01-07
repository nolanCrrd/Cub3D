#include "libft.h"
#include <stddef.h>

void	remove_spaces(char *s)
{
	size_t	i;
	size_t	j;

	if (s == NULL)
		return ;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}
