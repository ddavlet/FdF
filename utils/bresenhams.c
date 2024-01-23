/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenhams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:16:40 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/23 14:24:21 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t	*pixelstart;

	if (!img)
		ft_putendl_fd("Image does not exist", 2);
	if (!(x < img->width))
	{
		ft_putendl_fd("Pixel is out of bounds (axes x)", 2); // close window
		printf("iso_x: %u width: %u\n", x, img->width);
	}
	if (!(y < img->height))
	{
		ft_putendl_fd("Pixel is out of bounds (axes y)", 2); // close window
		printf("iso_y: %u height: %u\n", y, img->height);
	}
	pixelstart = &img->pixels[(y * img->width + x) * BPP];
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
	while (i <= vars->x)
	{
		draw_column_slope(vars, point, next_point);
		put_pixel(vars->img, point->iso_x, point->iso_y, 0xFF0000FF);
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
			// draw_line_negslope(vars, point, point->next);
			put_pixel(vars->img, point->iso_x, point->iso_y, 0xFF0000FF); // delete
			point = point->next;
		}
		coord = coord->next;
	}
}
