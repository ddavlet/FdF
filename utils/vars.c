/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:53:49 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/24 14:14:37 by ddavlety         ###   ########.fr       */
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
			point->iso_x = iso(vars, point, 'x');
			point->iso_y = iso(vars, point, 'y');
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
		return (NULL);
	}
	vars->x = 0;
	vars->y = 0;
	vars->coords = NULL;
	if (parse_coordinates(file_name, vars)) // check if width or height is 0 || ther is 1 point 1 line 1 column
		return (terminate_vars(&vars));
	vars->width = limits(vars->x, vars->x, 500);
	vars->height = limits(vars->y, vars->x, 500) / 1.8; //change max according to number of entries
	if (!init_pointcoord(&vars->coords, vars))
		return (terminate_vars(&vars));
	if (!init_window(vars))
		return (terminate_vars(&vars));
	if (!init_image(vars))
		return (terminate_vars(&vars));
	return (vars);
}
