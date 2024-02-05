/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:59:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/05 16:17:45 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

uint32_t	iso(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;
	float		rad;

	rad = vars->angle * PI / 180;
	x_iso = (uint32_t)(((float)point->x + (float)point->y)
			* cos(rad) - (0.5 * (float)vars->ymin));
	y_iso = (uint32_t)((- (float)point->x + (float)point->y + 1) * sin(rad)
			- (float)point->z + (float)vars->coords->points->x + vars->zmax
			+ vars->xmax * sin(rad));
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

uint32_t	iso_2(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;
	float		rad;

	rad = vars->angle * PI / 180;
	x_iso = (uint32_t)(((float)point->x - (float)point->y + 1) * cos(rad)
			- (float)vars->coords->points->x
			+ ((float)vars->ymax + (float)vars->xmax) * cos(rad));
	y_iso = (uint32_t)(((float)point->x + (float)point->y + 1) * sin(rad)
			- (float)point->z - (float)vars->coords->points->x * sin(rad)
			+ (float)vars->zmax);
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

uint32_t	iso_3(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;
	float		rad;

	rad = vars->angle * PI / 180;
	x_iso = (uint32_t)((float)point->x + (float)point->y * cos(rad) + 1)
		- cos(rad) * vars->ymin;
	y_iso = (uint32_t)(((float)point->y + 1) * sin(rad) - (float)point->z
			+ (float)vars->coords->points->x + (float)vars->zmax);
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}

uint32_t	iso_4(t_vars *vars, t_points *point, char axes)
{
	uint32_t	x_iso;
	uint32_t	y_iso;
	float		rad;

	rad = vars->angle * PI / 180;
	x_iso = (uint32_t)((float)point->x + (float)point->y + 1) * cos(rad) * 0.7
		- ((float)vars->coords->points->x + (float)vars->ymin) * sin(rad);
	y_iso = (uint32_t)(((float)point->y + 1) - (float)point->x * cos(rad) * 0.7
			- (float)point->z + (float)vars->coords->points->x
			+ (float)vars->zmax + (float)vars->xmax * cos(rad) * 0.7);
	if (axes == 'x')
		return (x_iso);
	else
		return (y_iso);
}
