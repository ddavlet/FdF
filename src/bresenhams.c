/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenhams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:16:40 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 16:18:33 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	put_pixel(mlx_image_t *img, t_pixel pixel, uint32_t y)
{
	t_color		color;
	uint8_t		*pixelstart;

	if (!img)
		ft_putendl_fd("Image does not exist", 2);
	if (!(pixel.x < img->width))
	{
		ft_putendl_fd("Pixel is out of bounds (axes x)", 2);
		printf("iso_x: %u width: %u\n", pixel.x, img->width);
	}
	if (!(pixel.y < img->height))
	{
		ft_putendl_fd("Pixel is out of bounds (axes y)", 2);
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
