/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:25:39 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/11 09:19:32 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_void(size_t num)
{
	if (!num)
		return (ft_putstr_fd("(nil)", 1));
	return (ft_putstr_fd("0x", 1) + ft_putnbr_hex_fd(num, 'a', 1));
}

static int	ft_print_param(char format, va_list argv)
{
	if (format == 'i' || format == 'd')
		return (ft_putnbr_fd(va_arg(argv, int), 1));
	if (format == 's')
		return (ft_putstr_fd(va_arg(argv, char *), 1));
	else if (format == 'u')
		return (ft_putunsnbr_fd(va_arg(argv, unsigned int), 1));
	else if (format == '\%')
		return (ft_putchar_fd('\%', 1));
	else if (format == 'c')
		return (ft_putchar_fd(va_arg(argv, int), 1));
	else if (format == 'p')
		return (ft_print_void(va_arg(argv, size_t)));
	else if (format == 'x')
		return (ft_putnbr_hex_fd(va_arg(argv, unsigned int), 'a', 1));
	else if (format == 'X')
		return (ft_putnbr_hex_fd(va_arg(argv, unsigned int), 'A', 1));
	return (0);
}

static char	ft_params(const char *txt, char *set)
{
	int		i;

	while (*txt)
	{
		i = 0;
		while (set[i])
		{
			if (set[i] == *txt)
				return (set[i]);
			i++;
		}
		txt++;
	}
	return (0);
}

static unsigned int	ft_aplflg(const char *txt, va_list argv)
{
	char	specif;

	specif = ft_params(txt, "cspdiuxX\%");
	return (ft_print_param(specif, argv));
}

int	ft_printf(const char *txt, ...)
{
	unsigned int	count;
	unsigned int	temp;
	va_list			argv;

	if (!txt)
		return (-1);
	va_start(argv, txt);
	count = 0;
	while (*txt)
	{
		if (*txt == '%')
		{
			temp = ft_aplflg((txt + 1), argv);
			txt += 2;
			count += temp;
		}
		else
		{
			ft_putchar_fd(*txt, 1);
			txt++;
			count++;
		}
	}
	va_end(argv);
	return (count);
}
