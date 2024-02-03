/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenhams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:16:40 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 13:22:08 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	draw_pixel(uint8_t *pixel, t_color color)
{
	*(pixel++) = color.red;
	*(pixel++) = color.green;
	*(pixel++) = color.blue;
	*(pixel++) = (uint8_t)(0xFF);
}

t_color	interpol_color(t_pixel pixel, float s)
{
	t_color	color;

	color.red = ((100 - s) * (pixel.color_to >> 16)
			+ s * (pixel.color_fr >> 16)) / 100;
	color.green = ((100 - s) * (pixel.color_to >> 8)
			+ s * (pixel.color_fr >> 8)) / 100;
	color.blue = ((100 - s) * (pixel.color_to & 0xFF)
			+ s * (pixel.color_fr & 0xFF)) / 100;
	// color.alpha = 255;
	return (color);
}

void	put_pixel(mlx_image_t *img, t_pixel pixel, uint32_t y)
{
	t_color		color;
	uint8_t		*pixelstart;

	if (!img)
		ft_putendl_fd("Image does not exist", 2);
	if (!(pixel.x < img->width))
	{
		ft_putendl_fd("Pixel is out of bounds (axes x)", 2); // close window
		printf("iso_x: %u width: %u\n", pixel.x, img->width);
	}
	if (!(pixel.y < img->height))
	{
		ft_putendl_fd("Pixel is out of bounds (axes y)", 2); // close window
		printf("iso_y: %u height: %u\n", pixel.y, img->height);
	}
	pixelstart = &img->pixels[(pixel.y * img->width + pixel.x) * BPP];
	color = interpol_color(pixel, labs((long)y -(long)pixel.y)
			* 100 / (labs((long)pixel.d_y) + 1));
	draw_pixel(pixelstart, color);
}

void	draw_column(t_vars *vars, t_coords *coords)
{
	uint32_t	i;
	t_points	*point;
	t_points	*next_point;

	i = 1;
	point = coords->points;
	next_point = coords->next->points;
	while (i <= vars->x && point)
	{
		draw_column_slope(vars, point, next_point);
		point = point->next;
		next_point = next_point->next;
		i++;
	}
}

void	put_iso_column(t_vars *vars)
{
	t_coords	*coord;

	coord = vars->coords;
	while (coord->next)
	{
		draw_column(vars, coord);
		coord = coord->next;
	}
}

void	put_iso_line(t_vars *vars)
{
	t_points	*point;
	t_coords	*coord;

	coord = vars->coords;
	while (coord)
	{
		point = coord->points;
		while (point->next)
		{
			draw_line_slope(vars, point, point->next);
			point = point->next;
		}
		coord = coord->next;
	}
}
