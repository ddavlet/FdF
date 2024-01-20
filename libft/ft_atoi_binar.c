/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_binar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:25:17 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/11 20:21:33 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_binar(const char *nptr, int i)
{
	int	nbr;

	nbr = 0;
	while (i-- && *nptr)
		nbr = nbr * 2 + (int)(*nptr++ - '0');
	return (nbr);
}
