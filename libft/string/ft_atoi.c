/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:41:54 by ehode             #+#    #+#             */
/*   Updated: 2026/01/07 13:32:50 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr, int *has_overflow)
{
	int	nb;
	int	sign;

	if (has_overflow)
		*has_overflow = 0;
	nb = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (has_overflow && nb > nb * 10 + *nptr - '0')
			*has_overflow = 1;
		nb = nb * 10 + *nptr - '0';
		nptr++;
	}
	return (nb * sign);
}
