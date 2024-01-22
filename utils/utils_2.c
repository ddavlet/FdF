/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:32:17 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/22 16:02:09 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

uint32_t	iso(uint32_t x, uint32_t y, int32_t z, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;

	x_iso = (uint32_t)((float)x + (float)z / sqrt(2) + y / sqrt(2)); //change 2-3 to some angle
	y_iso = (uint32_t)((float)y - (float)z / sqrt(2));
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

/*Protection of iso point overflow is in zoom hook*/
uint32_t	min_max_point(t_vars *vars, char axes)
{
	t_coords	*coord;
	t_points	*point;
	uint32_t	iso_x_max;
	uint32_t	iso_y_max;

	coord = vars->coords;
	iso_x_max = 0;
	iso_y_max = 0;
	while (coord)
	{
		point = coord->points;
		while (point)
		{
			if (point->iso_x > iso_x_max)
				iso_x_max = point->iso_x;
			if (point->iso_y > iso_y_max)
				iso_y_max = point->iso_y;
			point = point->next;
		}
		coord = coord->next;
	}
	if (axes == 'x')
		return (iso_x_max);
	else
		return (iso_y_max);
}

int32_t	zmax(t_vars *vars)
{
	t_coords	*coord;
	t_points	*points;
	int32_t		i;

	i = INT32_MIN;
	coord = vars->coords;
	while (coord)
	{
		points = coord->points;
		while (points)
		{
			if (points->z > i)
				i = points->z;
			points = points->next;
		}
		coord = coord->next;
	}
	return (i);
}

int32_t	zmin(t_vars *vars)
{
	t_coords	*coord;
	t_points	*points;
	int32_t		i;

	i = INT32_MAX;
	coord = vars->coords;
	while (coord)
	{
		points = coord->points;
		while (points)
		{
			if (points->z < i)
				i = points->z;
			points = points->next;
		}
		coord = coord->next;
	}
	return (i);
}
