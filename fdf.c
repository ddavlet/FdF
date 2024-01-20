/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:23:09 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/20 11:00:47 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	}
	if (!(y < img->height))
	{
		ft_putendl_fd("Pixel is out of bounds (axes y)", 2); // close window
	}

	pixelstart = &img->pixels[(y * img->width + x) * BPP];
	draw_pixel(pixelstart, color);
}

void	draw_line(t_vars *vars, t_points *column)
{
	long		d_y;
	long		d_x;
	long		slope_error;
	uint32_t	x;
	uint32_t	y;

	d_y = (long)column->next->iso_y - (long)column->iso_y; // should never overflow because of screen limit
	d_x = (long)column->next->iso_x - (long)column->iso_x; // should never overflow because of screen limit
	slope_error = 2 * labs(d_y) - d_x;
	x = column->iso_x;
	y = column->iso_y;
	put_pixel(vars->img, x, y, 0xFFFFFFFF);
	while (x != column->next->iso_x) //change this for negative/positive only
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
		if (d_x > 0) // open this
			x++;
		else
			x--;
		put_pixel(vars->img, x, y, 0xFFFFFFFF);
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
			draw_line(vars, point);
			put_pixel(vars->img, point->iso_x, point->iso_y, 0xFF0000FF); // delete
			point = point->next;
		}
		coord = coord->next;
	}
}

void	draw_column_111(t_vars *vars, t_points *line, t_points *next_line)
{
	long		d_y;
	long		d_x;
	long		slope_error;
	uint32_t	x;
	uint32_t	y;

	//test


	//test

	d_y = (long)next_line->iso_y - (long)line->iso_y; // should never overflow because of screen limit
	d_x = (long)next_line->iso_x - (long)line->iso_x; // should never overflow because of screen limit
	slope_error = d_x - 2 * labs(d_y);
	x = line->iso_x;
	y = line->iso_y;
// 		if (x > next_line->iso_x) {
//     // Swap the coordinates if needed
//    	 int temp = x;
//     x = next_line->iso_x;
//     next_line->iso_x = temp;

//     temp = y;
//     y = next_line->iso_y;
//     next_line->iso_y = temp;
// }
	put_pixel(vars->img, x, y, 0xFFFFFFFF);
	while (y != next_line->iso_y)
	{
		if (slope_error > 0)
		{
			if (d_y > 0)
				y++;
			else
				y--;
			slope_error += 2 * (d_y - labs(d_x));
		}
		else
			slope_error += 2 * labs(d_y);
		if (d_x > 0)
			x++;
		else if (d_x < 0)
			x--;
		put_pixel(vars->img, x, y, 0xFFFFFFFF);
	}
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
		draw_column_111(vars, point, next_point);
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

void	create_image(void *param)
{
	t_vars		*vars;
	uint32_t	color;
	uint32_t	x;
	uint32_t	y;

	x = 0;
	vars = param;
	color = create_trgb(get_r(0xFF00), get_g(0xFF00),
			get_b(0xFF00), get_t(0x000000FF));
	while (x < vars->img->width)
	{
		y = 0;
		while (y < vars->img->height)
			put_pixel(vars->img, x, y++, 0);
		x++;
	}
	x = 0;
	put_iso_line(vars);
	put_iso_column(vars);
}

int	create_window(t_vars *vars)
{
	if (mlx_image_to_window(vars->mlx, vars->img, LAYOUT_WIDTH / 2, LAYOUT_HEIGHT / 2) == -1)
	{
		mlx_close_window(vars->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(vars->mlx, ft_hook_buttons, vars);
	// mlx_scroll_hook(vars->mlx, ft_hook_scroll, vars); // do I need this?
	// mlx_mouse_hook(vars->mlx, ft_hook_mouse, vars); // do I need this?
	mlx_loop_hook(vars->mlx, create_image, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_vars	*vars;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <file with coordinates>", 1);
		return (1);
	}
	vars = init_vars(argv[1]);
	create_window(vars);
	terminate_vars(vars);
	return (0);
}
