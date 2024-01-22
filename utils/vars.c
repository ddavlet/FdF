/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:53:49 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/22 15:59:09 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	init_isometrics(t_vars *vars)
{
	t_coords	*coord;
	t_points	*point;

	coord = vars->coords;
	while (coord)
	{
		point = coord->points;
		while (point)
		{
			point->iso_x = iso(point->x, point->y, point->z, 'x');
			point->iso_y = iso(point->x, point->y, point->z, 'y');
			point = point->next;
		}
		coord = coord->next;
	}
}

void	*init_window(t_vars *vars)
{
	vars->mlx = mlx_init(min_max_point(vars, 'x') + LAYOUT_WIDTH,
			min_max_point(vars, 'y') + LAYOUT_HEIGHT, WINDOW_NAME, RESIZEABLE);
	if (!vars->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (NULL); // handle this NULL
	}
	return (vars->mlx);
}

mlx_image_t	*init_image(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx, vars->mlx->width - LAYOUT_WIDTH / 2,
			vars->mlx->height - LAYOUT_HEIGHT / 2);
	if (!vars->img)
	{
		mlx_close_window(vars->mlx);
		puts(mlx_strerror(mlx_errno));
		return (NULL); // handle this NULL
	}
	return (vars->img);
}

t_vars	*init_vars(char *file_name)
{
	t_vars		*vars;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
	{
		perror("Failed to allocate memmory");
		return (NULL);// catch it!
	}
	vars->x = 0;
	vars->y = 0;
	// vars->z = 6;
	vars->coords = NULL;
	parse_coordinates(file_name, vars); // check if width or height is 0
	vars->width = limits(vars->x, 1920);
	vars->height = limits(vars->y, 1080);
	vars->zoom = 0;
	init_pointcoord(&vars->coords, vars);
	// move_picture(vars);
	// init_isometrics(vars);
	init_window(vars);
	init_image(vars);
	return (vars);
}

void	terminate_vars(t_vars *vars)
{
	free_coords(&vars->coords);
	free(vars);
}
