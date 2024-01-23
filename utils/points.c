/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:02:30 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/23 18:28:55 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int32_t	init_z_points(t_vars *vars)
{
	t_coords	*coord;
	t_points	*points;
	int32_t		i;
	int32_t		x;

	// i = zmax(vars) - zmin(vars);
	i = vars->x;
	x = (int32_t)mmax(vars);
	coord = vars->coords;
	while (coord)
	{
		points = coord->points;
		while (points)
		{
			if (points->z != 0)
				points->z = (int32_t)(float)points->z / (float)i * (float)x;
			points = points->next;
		}
		coord = coord->next;
	}
	return (i);
}

t_points	*init_point(t_points **points, uint32_t x,
	uint32_t y, int32_t z)
{
	t_points	*point;
	t_points	*last;

	point = (t_points *)malloc(sizeof(t_points));
	if (!point)
		return (NULL); //deal with this return
	point->x = x;
	point->y = y;
	point->z = z;
	if (!*points)
	{
		*points = point;
		return (point);
	}
	last = *points;
	while (last->next)
		last = last->next;
	last->next = point;
	return (point);
}

t_points	*init_points(t_coords *coords, uint32_t step_x,
		uint32_t step_y, uint32_t line)
{
	t_points		*points;
	unsigned int	i;
	int32_t			z;

	i = 0;
	points = coords->points;
	while ((coords->coordinate)[i])
	{
		z = ft_atoi((coords->coordinate)[i]);
		points = init_point(&coords->points, step_x * (i + 1),
				step_y * line, z); // change z multiplier
		if (!points)
		{
			free_points(&coords->points);
			return (NULL); // dela with this NULL
		}
		i++;
		points->next = NULL;
		points = points->next;
	}
	return (coords->points);
}

void	init_pointcoord(t_coords **coords, t_vars *vars)
{
	t_coords	*coord;
	uint32_t	i;

	i = 1;
	coord = *coords;
	while (coord)
	{
		free_points(&coord->points);
		coord->points = init_points(coord, (vars->width - vars->zoom) / vars->x,
				(vars->height - vars->zoom) / vars->y, i); // change to varialbes to use zoom
		coord = coord->next;
		i++;
	}
	init_z_points(vars);
	// init_colors_points(vars); //ini
	move_picture(vars);
	init_isometrics(vars);
}

void	move_picture(t_vars *vars)
{
	t_coords	*coord;
	t_points	*point;
	// int32_t		zn;
	int32_t		zm;
	uint32_t	xm;

	// zn = zmin(vars);
	zm = zmax(vars);
	xm = mmax(vars);
	coord = vars->coords;
	while (coord)
	{
		point = coord->points;
		while (point)
		{
			// if (zn < 0)
				// point->x += (uint32_t)(abs(zn) / sqrt(2));
			if (zm != 0 || xm != 0)
				point->y += (uint32_t)(abs(zm) / sqrt(2) + xm / sqrt(6));
			point = point->next;
		}
		coord = coord->next;
	}
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
		- (uint32_t)(abs(zm) / sqrt(2) + xm / sqrt(6));
	y_iso = (uint32_t)((float)point->y - (float)point->z
			/ sqrt(2) - point->x / sqrt(6));
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}
