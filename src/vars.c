/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:53:49 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 14:10:38 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	change_projection(t_vars *vars,
		uint32_t (*iso)(t_vars *, t_points *, char))
{
	mlx_image_t	*tmp;

	tmp = vars->img;
	init_isometrics(vars, iso);
	if (!init_image(vars))
		terminate_vars(&vars);
	if (mlx_image_to_window(vars->mlx, vars->img,
			LAYOUT_WIDTH / 4, LAYOUT_HEIGHT / 4) == -1)
	{
		mlx_close_window(vars->mlx);
		perror(mlx_strerror(mlx_errno));
		return ;
	}
	mlx_delete_image(vars->mlx, tmp);
}

void	init_isometrics(t_vars *vars,
		uint32_t (*iso)(t_vars *, t_points *, char))
{
	t_coords	*coord;
	t_points	*point;

	coord = vars->coords;
	while (coord)
	{
		point = coord->points;
		while (point)
		{
			point->iso_x = iso(vars, point, 'x');
			point->iso_y = iso(vars, point, 'y');
			point = point->next;
		}
		coord = coord->next;
	}
}

void	*init_window(t_vars *vars)
{
	mlx_set_setting(MLX_DECORATED, true);
	vars->mlx = mlx_init(min_max_point(vars, 'x') + LAYOUT_WIDTH,
			min_max_point(vars, 'y') + LAYOUT_HEIGHT, WINDOW_NAME, RESIZEABLE);
	if (!vars->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (NULL);
	}
	return (vars->mlx);
}

mlx_image_t	*init_image(t_vars *vars)
{
	vars->img = mlx_new_image(vars->mlx,
			min_max_point(vars, 'x') + LAYOUT_WIDTH / 2,
			min_max_point(vars, 'y') + LAYOUT_HEIGHT / 2);
	if (!vars->img)
	{
		mlx_close_window(vars->mlx);
		puts(mlx_strerror(mlx_errno));
		return (NULL);
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
		return (NULL);
	}
	vars->x = 0;
	vars->y = 0;
	vars->coords = NULL;
	vars->angle = 30;
	if (parse_coordinates(file_name, vars)) // check if width or height is 0 || ther is 1 point 1 line 1 column
		return (terminate_vars(&vars));
	vars->width = limits(vars->x, vars->x, 800);
	vars->height = limits(vars->y, vars->x, 600) / 1.8;
	// vars->projec = iso_2;
	if (!init_pointcoord(&vars->coords, vars))
		return (terminate_vars(&vars));
	if (!init_window(vars))
		return (terminate_vars(&vars));
	if (!init_image(vars))
		return (terminate_vars(&vars));
	return (vars);
}
