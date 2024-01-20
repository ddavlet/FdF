/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:53:49 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/20 19:55:14 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
	vars->coords = NULL;
	// vars->img = NULL;
	// vars->mlx = NULL;
	// vars->win = NULL;
	parse_coordinates(file_name, vars); // check if width or height is 0
	init_pointcoord(&vars->coords, vars);
	vars->mlx = mlx_init(limits(vars->x, 1920),
			limits(vars->y, 1080), WINDOW_NAME, RESIZEABLE);
	if (!vars->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (NULL); // handle this NULL
	}
	vars->img = mlx_new_image(vars->mlx, vars->mlx->width - LAYOUT_WIDTH,
			vars->mlx->height - LAYOUT_HEIGHT);
	if (!vars->img)
	{
		mlx_close_window(vars->mlx);
		puts(mlx_strerror(mlx_errno));
		return (NULL); // handle this NULL
	}
	vars->width = vars->img->width;
	vars->height = vars->img->height;
	vars->zoom = 0;
	return (vars);
}

void	terminate_vars(t_vars *vars)
{
	free_coords(&vars->coords);
	free(vars);
}
