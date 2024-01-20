/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:08:17 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/11 09:26:41 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	i;

	i = 0;
	if (n == INT_MIN)
		return (ft_putstr_fd("-2147483648", fd));
	if (n == 0)
		return (ft_putchar_fd('0', fd));
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		i++;
	}
	if (n >= 10)
		i += ft_putnbr_fd(n / 10, fd);
	i += ft_putchar_fd(n % 10 + 48, fd);
	return (i);
}
