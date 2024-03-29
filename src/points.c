/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:02:30 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 16:45:37 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	init_z_points(t_vars *vars)
{
	t_coords	*coord;
	t_points	*points;
	int32_t		i;
	int32_t		x;

	i = vars->x;
	x = (int32_t)xmax(vars);
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
}

t_points	*init_point(t_points **points, uint32_t x,
	uint32_t y, int32_t z)
{
	t_points	*point;
	t_points	*last;

	point = (t_points *)malloc(sizeof(t_points));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->next = NULL;
	if (!*points)
	{
		*points = point;
		return (point);
	}
	last = *points;
	while (last->next)
		last = last->next;
	last->next = point;
	point->next = NULL;
	return (point);
}

t_points	*init_points(t_coords *coords, uint32_t step_x,
		uint32_t step_y, uint32_t line)
{
	t_points		*points;
	unsigned int	i;

	i = 0;
	points = coords->points;
	while ((coords->coordinate)[i])
	{
		points = init_point(&coords->points, step_x * (i + 1),
				step_y * line, ft_atoi((coords->coordinate)[i]));
		if (!points)
		{
			perror("Failed to create one point");
			return (free_points(&coords->points));
		}
		i++;
		points = points->next;
	}
	return (coords->points);
}

void	init_ext_values(t_vars *vars)
{
	yext(vars);
	vars->zmax = zmax(vars);
}

t_coords	*init_pointcoord(t_coords **coords, t_vars *vars)
{
	t_coords	*coord;
	uint32_t	i;

	i = 1;
	coord = *coords;
	while (coord)
	{
		free_points(&coord->points);
		coord->points = init_points(coord, (vars->width) / vars->x,
				(vars->height) / vars->y, i);
		if (!coord->points)
		{
			perror("Failed to create points");
			return (free_coords(coords));
		}
		coord = coord->next;
		i++;
	}
	if (zmax(vars) < 25)
		init_z_points(vars);
	init_colors_points(vars);
	init_ext_values(vars);
	init_isometrics(vars, iso_2);
	return (*coords);
}
