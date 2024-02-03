/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:20 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 14:14:39 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
	if (mlx_is_key_down(vars->mlx, MLX_KEY_1))
		change_projection(vars, iso);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_2))
		change_projection(vars, iso_2);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_3))
		change_projection(vars, iso_3);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_4))
		change_projection(vars, iso_4);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_E))
		vars->angle -= 1;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_Q))
		vars->angle += 1;
}
