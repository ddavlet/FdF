/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:11:12 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/11 09:26:47 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex_fd(unsigned int num, char base, int fd)
{
	unsigned int	remainder;
	int				i;

	remainder = 0;
	i = 1;
	if (num >= 16)
		i += ft_putnbr_hex_fd(num / 16, base, fd);
	remainder = num % 16;
	if (remainder < 10)
		ft_putchar_fd('0' + remainder, fd);
	else
		ft_putchar_fd(base + remainder - 10, fd);
	return (i);
}
