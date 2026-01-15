/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_near_elmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:05:37 by ncorrear          #+#    #+#             */
/*   Updated: 2026/01/15 11:05:50 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

/**
 * @brief return the difference of position of the nearby charset
 * value on the map grid
 *
 * @param grid map grid
 * @param charset element to find near
 * @param pos position to look arround
 * @return defference btetween pos and the found element / NULL if not find
 */
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
