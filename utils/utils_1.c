/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:59:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/20 19:53:48 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

uint32_t	ft_arraystrlen(char **array)
{
	uint32_t	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	clear_exit(char **ptr, int error) // what is that for?
{
	char	**tmp;

	tmp = ptr;
	if (ptr)
	{
		while (*ptr)
			free(*ptr++);
		free(tmp);
	}
	if (error)
	{
		perror("Error parsing while file");
		exit (1);
	}
}

uint32_t	limits(uint32_t num, uint32_t max)
{
	if (num > max)
		return (max);
	num = SIZE * log2(num) * log2(num);
	if (num >= max)
		return (max - 1);
	// if (num == 0)
	// 	return (0);
	if (num < 300)  // change to WIDTH && HEIGHT
		return (300);
	return (num);
}

void	min_max_img(t_vars *vars)
{
	if (vars->height >= vars->img->height
		|| vars->width >= vars->img->width)
	{
		vars->height = vars->img->height;
		vars->width = vars->img->width;
	}
	if (vars->height <= ZOOM + 1
		|| vars->width <= ZOOM + 1)
	{
		vars->height = ZOOM + 1;
		vars->width = ZOOM + 1;
	}
}

// static void ft_error(void) //use this!
// {
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }
