/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:59:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/27 15:53:43 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

uint32_t	ft_arraystrlen(char **array)
{
	uint32_t	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

uint32_t	limits(uint32_t num, uint32_t num2, uint32_t max)
{
	if (num < 15 && num2 < 15)
		max = 400;
	if (num2 >= num)
		num = (uint32_t)(((float)num / (float)num2) * (float)max);
	else
		num = (uint32_t)(((float)num2 / (float)num) * (float)max);
	return (num);
}

uint32_t	htoi_color(const char *str)
{
	uint32_t	i;
	uint32_t	result;

	if (!str)
		return (0xFFFFFF);
	str += 3;
	i = 0;
	result = 0;
	while (*str && *str != '\n')
	{
		if (*str >= '0' && *str <= '9')
			i = *str++ - '0';
		else if (*str >= 'a' && *str <= 'f')
			i = *str++ - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			i = *str++ - 'A' + 10;
		else
		{
			perror("Error parsing color");
			return (UINT32_MAX);
		}
		result = result * 16 + i;
	}
	return (result);
}

