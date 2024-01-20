/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:47:21 by ddavlety          #+#    #+#             */
/*   Updated: 2023/11/15 16:46:57 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}

static int	check_beyond_int(int nbr, char n, int sign)
{
	if (sign == 1)
	{
		if (nbr == 214748364 && n - '0' > 7)
			return (2147483647);
	}
	else if (sign == -1)
	{
		if (nbr == 214748364 && n - '0' > 8)
			return (-2147483648);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	while (ft_isspace(*nptr) != 0)
	{
		nptr++;
	}
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		if (check_beyond_int(nbr, *nptr, sign) != 0)
			return (check_beyond_int(nbr, *nptr, sign));
		nbr = nbr * 10 + (int)(*nptr - '0');
		nptr++;
	}
	return (nbr * sign);
}
