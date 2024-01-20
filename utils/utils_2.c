/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:32:17 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/20 19:59:20 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

uint32_t	iso(uint32_t x, uint32_t y, uint32_t z, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;

	x_iso = (uint32_t)((float)x + (float)z / sqrt(2));
	// y_iso = (x + 2 * y - z) / sqrt(5);
	y_iso = (uint32_t)((float)y - (float)z / sqrt(2));
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

int	min_max_point(t_vars *vars)
{
	t_coords	*coord;
	t_points	*point;

	coord = vars->coords;
	while (coord->next)
		coord = coord->next;
	point = coord->points;
	while (point->next)
		point = point->next;
	if (point->iso_x > vars->width)
	{
		vars->zoom++;
		return (1);
	}
	else if (point->iso_y > vars->height)
	{
		vars->zoom++;
		return (1);
	}
	return (0);
}
