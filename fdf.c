/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:23:09 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/24 14:05:41 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	create_image(void *param)
{
	t_vars		*vars;
	uint32_t	x;
	uint32_t	y;

	x = 0;
	vars = param;
	while (x < vars->img->width)
	{
		y = 0;
		while (y < vars->img->height)
			clean_pixel(vars->img, x, y++);
		x++;
	}
	x = 0;
	put_iso_line(vars);
	put_iso_column(vars);
}

int	create_window(t_vars *vars)
{
	if (mlx_image_to_window(vars->mlx, vars->img,
			LAYOUT_WIDTH / 4, LAYOUT_HEIGHT / 4) == -1)
	{
		mlx_close_window(vars->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(vars->mlx, ft_hook_buttons, vars);
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
	if (!vars)
		return (1);
	if (create_window(vars))
	{
		terminate_vars(&vars);
		return (1);
	}
	terminate_vars(&vars);
	return (0);
}
