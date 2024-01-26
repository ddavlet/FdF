/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:59:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/26 22:23:59 by ddavlety         ###   ########.fr       */
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

uint32_t	iso(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;

	x_iso = (uint32_t)((float)point->x + 1.9 * (float)point->y)
		- 1.9 * vars->ymin;
	y_iso = (uint32_t)((float)point->y - (float)point->z
			/ sqrt(2) - point->x / sqrt(6) + vars->zmax + vars->xmax);
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

uint32_t	iso_2(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;

	x_iso = (uint32_t)(((float)point->x - (float)point->y) * 0.8944
			- vars->coords->points->x + vars->ymax);
	y_iso = (uint32_t)(((float)point->x + (float)point->y + 1) * 0.4472
			- (float)point->z - vars->coords->points->x + vars->zmax);
	// x_iso = point->x;
	// y_iso = point->y;
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}
