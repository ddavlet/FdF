/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:32:17 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/21 21:12:29 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

uint32_t	iso(uint32_t x, uint32_t y, uint32_t z, char axes)
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
int	min_max_point(t_vars *vars)
{
	t_coords	*coord;
	t_points	*point;

	coord = vars->coords;
	while (coord)
	{
		point = coord->points;
		while (point)
		{
			if (point->iso_x > (vars->width - 1))
			{
				vars->zoom++;
				return (1);
			}
			else if (point->iso_y > vars->height)
			{
				vars->zoom++;
				return (1);
			}
			point = point->next;
		}
		coord = coord->next;
	}
	return (0);
}
