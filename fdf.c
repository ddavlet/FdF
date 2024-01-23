/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:23:09 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/23 18:25:12 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	img_limit(t_vars *vars)
{
	if (min_max_point(vars, 'x') > 1900)
	{
		vars->zoom++;
		return (1);
	}
	if (min_max_point(vars, 'y') > 1000)
	{
		vars->x++;
		vars->zoom++;
		return (1);
	}
	return (0);
}

void	create_image(void *param)
{
	t_vars		*vars;
	uint32_t	x;
	uint32_t	y;
	// uint32_t	color;

	x = 0;
	vars = param;
	while (x < vars->img->width)
	{
		y = 0;
		while (y < vars->img->height)
			put_pixel(vars->img, x, y++, 0x00FF);
		x++;
	}
	x = 0;
	// init_pointcoord(&vars->coords, vars);
	// if (img_limit(vars))
	// 	init_pointcoord(&vars->coords, vars);
	put_iso_line(vars);
	put_iso_column(vars);
}

int	create_window(t_vars *vars)
{
	if (mlx_image_to_window(vars->mlx, vars->img, LAYOUT_WIDTH / 4, LAYOUT_HEIGHT / 4) == -1)
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
