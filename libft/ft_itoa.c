/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:38:23 by ddavlety          #+#    #+#             */
/*   Updated: 2023/11/18 15:31:41 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(int n)
{
	int	i;

	i = 1;
	if (n == INT_MIN)
		return (11);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	if (n >= 10)
		i += ft_counter (n / 10);
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		bytes;
	long	i;

	i = (long)n;
	bytes = ft_counter(n);
	ptr = (char *)malloc((bytes + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ptr[bytes--] = '\0';
	if (i == 0)
		ptr[bytes] = '0';
	if (i < 0)
	{
		ptr[0] = '-';
		i *= -1;
	}
	while (i != 0 && bytes > -1)
	{
		ptr[bytes] = i % 10 + 48;
		bytes--;
		i /= 10;
	}
	return (ptr);
}
