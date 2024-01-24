/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:15 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/24 15:39:30 by ddavlety         ###   ########.fr       */
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

	d_x = (long)next_column->iso_x - (long)column->iso_x;
	d_y = (long)next_column->iso_y - (long)column->iso_y;
	if (labs(d_y) > labs(d_x))
		return (draw_column_slope(vars, column, next_column));
	if (d_x < 0)
		return (draw_line_negslope(vars, column, next_column));
	x = column->iso_x;
	y = column->iso_y;
	slope_error = 2 * labs(d_y) - d_x;
	while (x < next_column->iso_x)
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
		put_pixel(vars->img, x, y, column->color);
	}
}

void	draw_column_negslope(t_vars *vars, t_points *line, t_points *next_line)
{
	long		d_y;
	long		d_x;
	long		slope_error;
	uint32_t	x;
	uint32_t	y;

	d_y = (long)line->iso_y - (long)next_line->iso_y;
	d_x = (long)line->iso_x - (long)next_line->iso_x;
	slope_error = 2 * labs(d_x) - d_y;
	x = next_line->iso_x;
	y = next_line->iso_y;
	while (y < line->iso_y)
	{
		if (slope_error > 0)
		{
			if (d_x > 0)
				x++;
			else
				x--;
			slope_error += 2 * (labs(d_x) - d_y);
		}
		else
			slope_error += 2 * labs(d_x);
		y++;
		put_pixel(vars->img, x, y, next_line->color);
	}
}

void	draw_column_slope(t_vars *vars, t_points *line, t_points *next_line)
{
	long		d_y;
	long		d_x;
	long		slope_error;
	uint32_t	x;
	uint32_t	y;

	d_x = (long)next_line->iso_x - (long)line->iso_x;
	d_y = (long)next_line->iso_y - (long)line->iso_y;
	if (labs(d_x) > labs(d_y))
		return (draw_line_slope(vars, line, next_line));
	if (d_y < 0)
		return (draw_column_negslope(vars, line, next_line));
	x = line->iso_x;
	y = line->iso_y;
	slope_error = 2 * labs(d_x) - d_y;
	while (y < next_line->iso_y) //change this for negative/positive only
	{
		if (slope_error > 0)
		{
			if (d_x > 0)
				x++;
			else
				x--;
			slope_error += 2 * (labs(d_x) - d_y);
		}
		else
			slope_error += 2 * labs(d_x);
		y++;
		put_pixel(vars->img, x, y, line->color);
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
		put_pixel(vars->img, x, y, next_column->color);
	}
}
