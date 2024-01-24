/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:15 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/24 17:37:20 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*iso_x and iso_y should never overflow because of screen limit*/
void	draw_line_slope(t_vars *vars, t_points *column, t_points *next_column)
{
	t_pixel	pixel;

	pixel.d_x = (long)next_column->iso_x - (long)column->iso_x;
	pixel.d_y = (long)next_column->iso_y - (long)column->iso_y;
	if (labs(pixel.d_y) > labs(pixel.d_x))
		return (draw_column_slope(vars, column, next_column));
	if (pixel.d_x < 0)
		return (draw_line_negslope(vars, column, next_column));
	pixel.x = column->iso_x;
	pixel.y = column->iso_y;
	pixel.color_fr = column->color;
	pixel.color_to = next_column->color;
	pixel.slope_error = 2 * labs(pixel.d_y) - pixel.d_x;
	while (pixel.x < next_column->iso_x)
	{
		if (pixel.slope_error > 0)
		{
			if (pixel.d_y > 0)
				pixel.y++;
			else
				pixel.y--;
			pixel.slope_error += 2 * (labs(pixel.d_y) - pixel.d_x);
		}
		else
			pixel.slope_error += 2 * labs(pixel.d_y);
		pixel.x++;
		put_pixel(vars->img, pixel, next_column->iso_y);
	}
}

void	draw_column_negslope(t_vars *vars, t_points *line, t_points *next_line)
{
	t_pixel	pixel;

	pixel.d_y = (long)line->iso_y - (long)next_line->iso_y;
	pixel.d_x = (long)line->iso_x - (long)next_line->iso_x;
	pixel.slope_error = 2 * labs(pixel.d_x) - pixel.d_y;
	pixel.x = next_line->iso_x;
	pixel.y = next_line->iso_y;
	pixel.color_fr = line->color;
	pixel.color_to = next_line->color;
	while (pixel.y < line->iso_y)
	{
		if (pixel.slope_error > 0)
		{
			if (pixel.d_x > 0)
				pixel.x++;
			else
				pixel.x--;
			pixel.slope_error += 2 * (labs(pixel.d_x) - pixel.d_y);
		}
		else
			pixel.slope_error += 2 * labs(pixel.d_x);
		pixel.y++;
		put_pixel(vars->img, pixel, line->iso_y);
	}
}

void	draw_column_slope(t_vars *vars, t_points *line, t_points *next_line)
{
	t_pixel	pixel;

	pixel.d_x = (long)next_line->iso_x - (long)line->iso_x;
	pixel.d_y = (long)next_line->iso_y - (long)line->iso_y;
	if (labs(pixel.d_x) > labs(pixel.d_y))
		return (draw_line_slope(vars, line, next_line));
	if (pixel.d_y < 0)
		return (draw_column_negslope(vars, line, next_line));
	pixel.x = line->iso_x;
	pixel.y = line->iso_y;
	pixel.color_fr = line->color;
	pixel.color_to = next_line->color;
	pixel.slope_error = 2 * labs(pixel.d_x) - pixel.d_y;
	while (pixel.y < next_line->iso_y)
	{
		if (pixel.slope_error > 0)
		{
			if (pixel.d_x > 0)
				pixel.x++;
			else
				pixel.x--;
			pixel.slope_error += 2 * (labs(pixel.d_x) - pixel.d_y);
		}
		else
			pixel.slope_error += 2 * labs(pixel.d_x);
		pixel.y++;
		put_pixel(vars->img, pixel, next_line->iso_y);
	}
}

void	draw_line_negslope(t_vars *vars, t_points *column, t_points *next_column)
{
	t_pixel	pixel;


	pixel.d_x = (long)column->iso_x - (long)next_column->iso_x;
	pixel.d_y = (long)column->iso_y - (long)next_column->iso_y;
	pixel.x = next_column->iso_x;
	pixel.y = next_column->iso_y;
	pixel.color_fr = column->color;
	pixel.color_to = next_column->color;
	pixel.slope_error = 2 * labs(pixel.d_y) - pixel.d_x;
	while (pixel.x < column->iso_x)
	{
		if (pixel.slope_error > 0)
		{
			if (pixel.d_y > 0)
				pixel.y++;
			else
				pixel.y--;
			pixel.slope_error += 2 * (labs(pixel.d_y) - pixel.d_x);
		}
		else
			pixel.slope_error += 2 * labs(pixel.d_y);
		pixel.x++;
		put_pixel(vars->img, pixel, column->iso_x);
	}
}
