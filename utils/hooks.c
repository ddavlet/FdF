/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:20 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/22 12:08:51 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*100 is never more than dimensions. Overflow should never be a case*/
void	ft_hook_scroll(double xdelta, double ydelta, void *param)
{
	t_vars	*vars;

	vars = param;
	printf("x: %f\ny: %f", xdelta, ydelta);
	if (ydelta < 0)
		if (vars->zoom < (vars->height - 100)
			&& vars->zoom < (vars->width - 100))
			vars->zoom += 2;
	if (ydelta > 0)
		vars->zoom -= 2;
}

void	change_z(uint32_t *z, char sign) // ??
{
	if (sign == '-')
	{
		if ((*z) > 0)
			(*z) -= 1;
	}
	else
	{
		if ((*z) < 15)
			(*z) += 1;
	}
}

void	ft_hook_buttons(void *param)
{
	t_vars	*vars;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		vars->img->nstances[0].y -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		vars->img->nstances[0].y += 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->img->nstances[0].x -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		vars->img->nstances[0].x += 5;
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_MINUS))
	// 	change_z(&vars->z, '-');
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_EQUAL))
	// 	change_z(&vars->z, '-');
}

void	ft_hook_mouse(mouse_key_t button, action_t action,
		modifier_key_t mods, void *param) //do I need this?
{
	// t_vars	*vars;

	// vars = param;
	(void)param;
	ft_printf("%i\n%i\n%i", button, action, mods);
}
