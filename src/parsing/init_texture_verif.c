#include "libft.h"
#include "parsing.h"

static int	is_valid_color(char *color)
{
	int	val;
	int	as_overflow;

	val = ft_atoi(color, &as_overflow);
	if (val > 255 || val < 0 || as_overflow)
		return (0);
	return (1);
}

/**
 * @brief Return a boolean that say if the color code is rga ok
 *
 * @param color 
 * @return 1 if ok / 0 else
 */
int	is_valid_rgb(char *color)
{
	if (ft_isdigit(color[1]) || color[1] == '+' || color[1] == '-')
	{
		if (!is_valid_color(color + 1))
			return (0);
	}
	color = ft_strchr(color, ',');
	if (color++ == NULL || !*color)
		return (0);
	if (ft_isdigit(color[0]) || color[0] == '+' || color[0] == '-')
	{
		if (!is_valid_color(color))
			return (0);
	}
	color = ft_strchr(color, ',');
	if (color++ == NULL || !*color)
		return (0);
	if (ft_isdigit(color[0]) || color[0] == '+' || color[0] == '-')
	{
		if (!is_valid_color(color))
			return (0);
	}
	return (1);
}
