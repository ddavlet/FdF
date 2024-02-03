/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:51:55 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 16:42:59 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	*free_points(t_points **points)
{
	t_points	*point;
	t_points	*tmp;

	point = *points;
	while (point)
	{
		tmp = point->next;
		free(point);
		point = tmp;
	}
	*points = NULL;
	return (NULL);
}

void	*free_coordinates(char **ptr)
{
	char	**tmp;

	tmp = ptr;
	while (*tmp)
	{
		free(*tmp++);
	}
	free (ptr);
	return (NULL);
}

void	*free_coords(t_coords **coords)
{
	t_coords	*coord;
	t_coords	*tmp;

	coord = *coords;
	while (coord)
	{
		tmp = coord->next;
		if (coord->coordinate)
			free_coordinates(coord->coordinate);
		if (coord->points)
			free_points(&coord->points);
		if (coord)
			free(coord);
		coord = tmp;
	}
	*coords = NULL;
	return (NULL);
}

void	*terminate_vars(t_vars **vars)
{
	if (*vars && (*vars)->coords)
		free_coords(&(*vars)->coords);
	if (*vars)
		free(*vars);
	*vars = NULL;
	return (NULL);
}
