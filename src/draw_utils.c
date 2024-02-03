/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:15:15 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 17:27:36 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	init_pixel(t_pixel *pixel, t_points *prev, t_points *next)
{
	(*pixel).d_x = (long)next->iso_x - (long)prev->iso_x;
	(*pixel).d_y = (long)next->iso_y - (long)prev->iso_y;
	(*pixel).x = prev->iso_x;
	(*pixel).y = prev->iso_y;
	(*pixel).color_fr = prev->color;
	(*pixel).color_to = next->color;
	(*pixel).slope_error = 2 * labs((*pixel).d_y) - (*pixel).d_x;
}

/*iso_x and iso_y should never overflow because of screen limit*/
void	draw_line_slope(t_vars *vars, t_points *column, t_points *next_column)
{
	t_pixel	pixel;

	init_pixel(&pixel, column, next_column);
	if (labs(pixel.d_y) > labs(pixel.d_x))
		return (draw_column_slope(vars, column, next_column));
	if (pixel.d_x < 0)
		return (draw_line_negslope(vars, column, next_column));
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

	init_pixel(&pixel, next_line, line);
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

	init_pixel(&pixel, line, next_line);
	if (labs(pixel.d_x) > labs(pixel.d_y))
		return (draw_line_slope(vars, line, next_line));
	if (pixel.d_y < 0)
		return (draw_column_negslope(vars, line, next_line));
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

void	draw_line_negslope(t_vars *vars,
				t_points *column, t_points *next_column)
{
	t_pixel	pixel;

	init_pixel(&pixel, next_column, column);
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
		put_pixel(vars->img, pixel, column->iso_y);
	}
}
