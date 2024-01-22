/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:51:55 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/22 11:20:47 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_points(t_points **points)
{
	t_points	*tmp;

	tmp = *points;
	while (tmp)
	{
		free(tmp);
		tmp = tmp->next;
	}
	*points = NULL;
}

void	free_coordinates(char **ptr)
{
	char	**tmp;

	tmp = ptr;
	while (*ptr)
	{
		free(*ptr++);
	}
	free (tmp);
}

void	free_coords(t_coords **coords)
{
	t_coords	*coord;

	coord = *coords;
	while (coord)
	{
		free_coordinates(coord->coordinate);
		free_points(&coord->points);
		free(coord);
		coord = coord->next;
	}
}

