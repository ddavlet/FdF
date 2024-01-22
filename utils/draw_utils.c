/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:15 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/22 16:21:46 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*iso_x and iso_y should never overflow because of screen limit*/
void	draw_line_slope(t_vars *vars, t_points *column, t_points *next_column)
{
	long		d_y;
	long		d_x;
	long		slope_error;
	uint32_t	x;
	uint32_t	y;

	d_x = (long)next_column->iso_x - (long)column->iso_x; // should never overflow because of screen limit
	d_y = (long)next_column->iso_y - (long)column->iso_y; // should never overflow because of screen limit
	if (d_y > labs(d_x))
		return (draw_column_slope(vars, column, next_column));
	if (d_x < 0)
		return (draw_line_negslope(vars, column, next_column));
	x = column->iso_x;
	y = column->iso_y;
	slope_error = 2 * labs(d_y) - d_x;
	while (x < next_column->iso_x) //change this for negative/positive only
	{
		if (slope_error > 0)
		{
			if (d_y > 0)
				y++;
			else
				y--;
			slope_error += 2 * (labs(d_y) - d_x);
		}
		else
			slope_error += 2 * labs(d_y);
		x++;
		put_pixel(vars->img, x, y, 0xFFFFFFFF);
	}
}

void	draw_column_negslope(t_vars *vars, t_points *line, t_points *next_line)
{
	long		d_y;
	long		d_x;
	long		slope_error;
	uint32_t	x;
	uint32_t	y;

	d_x = (long)line->iso_y - (long)next_line->iso_y; // should never overflow because of screen limit
	d_y = (long)line->iso_x - (long)next_line->iso_x; // should never overflow because of screen limit
	// if (d_y > 1.5 * labs(d_x))
	// 	return (draw_line_negslope(vars, line, next_line));
	slope_error = 2 * labs(d_y) - d_x;
	y = next_line->iso_x;
	x = next_line->iso_y;
	while (x < line->iso_x)
	{
		if (slope_error > 0)
		{
			if (d_y > 0)
				y++;
			else
				y--;
			slope_error += 2 * (labs(d_y) - d_x);
		}
		else
			slope_error += 2 * labs(d_y);
		if (d_x > 0)
			x++;
		put_pixel(vars->img, y, x, 0xFFFFFFFF);
	}
}

void	draw_column_slope(t_vars *vars, t_points *line, t_points *next_line)
{
	long		d_y;
	long		d_x;
	long		slope_error;
	uint32_t	x;
	uint32_t	y;

	d_y = (long)next_line->iso_x - (long)line->iso_x; // should never overflow because of screen limit
	d_x = (long)next_line->iso_y - (long)line->iso_y; // should never overflow because of screen limit
	if (d_y > labs(d_x))
		return (draw_line_slope(vars, line, next_line));
	if (d_x < 0)
		return (draw_column_negslope(vars, line, next_line));
	y = line->iso_x;
	x = line->iso_y;
	slope_error = 2 * labs(d_y) - d_x;
	while (x < next_line->iso_y) //change this for negative/positive only
	{
		if (slope_error > 0)
		{
			if (d_y > 0)
				y++;
			else
				y--;
			slope_error += 2 * (labs(d_y) - d_x);
		}
		else
			slope_error += 2 * labs(d_y);
		x++;
		put_pixel(vars->img, y, x, 0xFFFFFFFF);
	}
}

void	draw_line_negslope(t_vars *vars, t_points *column, t_points *next_column)
{
	long		d_y;
	long		d_x;
	long		slope_error;
	uint32_t	x;
	uint32_t	y;

	d_x = (long)column->iso_x - (long)next_column->iso_x; // should never overflow because of screen limit
	d_y = (long)column->iso_y - (long)next_column->iso_y; // should never overflow because of screen limit
	x = next_column->iso_x;
	y = next_column->iso_y;
	slope_error = 2 * labs(d_y) - d_x;
	while (x < column->iso_x) //change this for negative/positive only
	{
		if (slope_error > 0)
		{
			if (d_y > 0)
				y++;
			else
				y--;
			slope_error += 2 * (labs(d_y) - d_x);
		}
		else
			slope_error += 2 * labs(d_y);
		x++;
		put_pixel(vars->img, x, y, 0xFFFFFFFF);
	}
}
