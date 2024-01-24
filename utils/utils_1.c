/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:59:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/24 20:18:39 by ddavlety         ###   ########.fr       */
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

// void	clear_exit(char **ptr, int error) // what is that for?
// {
// 	char	**tmp;

// 	tmp = ptr;
// 	if (ptr)
// 	{
// 		while (*ptr)
// 			free(*ptr++);
// 		free(tmp);
// 	}
// 	if (error)
// 	{
// 		perror("Error parsing while file");
// 		exit (1);
// 	}
// }

uint32_t	limits(uint32_t num, uint32_t num2, uint32_t max)
{
	if (num < 25 || num2 < 25)
		max = 300;
	num = (uint32_t)((float)num / (float)num2) * (float)max;
	if (num < 300) // change to WIDTH && HEIGHT
		return (300);
	return (num);
}

uint32_t	htoi_color(const char *str)
{
	uint32_t	i;
	uint32_t	result;

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

uint32_t	iso(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;
	int32_t		zm;
	uint32_t	xm;

	zm = zmax(vars);
	xm = mmax(vars);
	x_iso = (uint32_t)((float)point->x + 1.9 * (float)point->y)
		- 1.9 * (uint32_t)(abs(zm) / sqrt(2) + xm / sqrt(6));
	y_iso = (uint32_t)((float)point->y - (float)point->z
			/ sqrt(2) - point->x / sqrt(6));
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}
