/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:26:20 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/17 16:50:22 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_hook_scroll(double xdelta, double ydelta, void *param)
{
	t_vars	*vars;

	vars = param;
	printf("x: %f\ny: %f", xdelta, ydelta);
	if (ydelta < 0)
	{
		vars->height -= ZOOM;
		vars->width -= ZOOM;
	}
	if (ydelta > 0)
	{
		vars->height += ZOOM;
		vars->width += ZOOM;
	}
	min_max_img(vars);
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
}

void	ft_hook_mouse(mouse_key_t button, action_t action,
		modifier_key_t mods, void *param) //do I need this?
{
	t_vars	*vars;

	vars = param;
	ft_printf("%i\n%i\n%i", button, action, mods);
}
