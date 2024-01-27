/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:59:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/27 20:15:28 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

uint32_t	iso(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;

	x_iso = (uint32_t)((float)point->x + (float)point->y) * 0.8944
		- vars->coords->points->x - 0.8944 * vars->ymin;
	y_iso = (uint32_t)((- (float)point->x + (float)point->y + 1) * 0.4472
			- (float)point->z + vars->coords->points->x + vars->zmax + vars->xmax * 0.4472);
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

uint32_t	iso_2(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;

	x_iso = (uint32_t)(((float)point->x - (float)point->y + 1) * 0.8944
			- vars->coords->points->x + vars->ymax);
	y_iso = (uint32_t)(((float)point->x + (float)point->y + 1) * 0.4472
			- (float)point->z - vars->coords->points->x + vars->zmax);
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

uint32_t	iso_3(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;

	x_iso = (uint32_t)((float)point->x + (float)point->y *  0.8944 + 1)
		- vars->coords->points->x - 0.8944 * vars->ymin;
	y_iso = (uint32_t)(((float)point->y + 1) * 0.4472
			- (float)point->z + vars->coords->points->x + vars->zmax);
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

uint32_t	iso_4(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;

	x_iso = (uint32_t)((float)point->x + (float)point->y + 1) * 0.8944 * 0.7
		- vars->coords->points->x - 0.8944 * vars->ymin * 0.5;
	y_iso = (uint32_t)((- (float)point->x + (float)point->y + 1) * 0.8944 * 0.7
			- (float)point->z + vars->coords->points->x + vars->zmax + vars->xmax * 0.8944 * 0.7);
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

uint32_t	iso_5(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;

	(void)vars;
	x_iso = (uint32_t)((float)point->x + (float)point->z) * 0.8944 * 0.5;
	y_iso = (uint32_t)((float)point->y + (float)point->z) * 0.8944 * 0.5;
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}
