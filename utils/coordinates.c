/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:51:55 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/22 16:02:40 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	move_picture(t_vars *vars)
{
	t_coords	*coord;
	t_points	*point;
	int32_t		zn;
	int32_t		zm;

	zn = zmin(vars);
	zm = zmax(vars);
	coord = vars->coords;
	while (coord)
	{
		point = coord->points;
		while (point)
		{
			if (zn < 0)
				point->x += (uint32_t)(abs(zn) / sqrt(2));
			if (zm > 0)
				point->y += (uint32_t)(abs(zm) / sqrt(2));
			point = point->next;
		}
		coord = coord->next;
	}
}

t_points	*init_point(t_points **points, uint32_t x,
	uint32_t y, int32_t z)
{
	t_points	*point;
	t_points	*last;

	point = (t_points *)malloc(sizeof(t_points));
	if (!point)
		return (NULL); //deal with this return
	point->x = x;
	point->y = y;
	point->z = 1000 / (1 + pow(2.71828, (-0.01 * z))) - 500;
	if (!*points)
	{
		*points = point;
		return (point);
	}
	last = *points;
	while (last->next)
		last = last->next;
	last->next = point;
	return (point);
}

t_points	*init_points(t_coords *coords, uint32_t step_x,
		uint32_t step_y, unsigned int line)
{
	t_points		*points;
	unsigned int	i;
	int32_t			z;

	i = 0;
	points = coords->points;
	while ((coords->coordinate)[i])
	{
		z = ft_atoi((coords->coordinate)[i]);
		points = init_point(&coords->points, step_x * (i + 1),
				step_y * line, z); // change z multiplier
		if (!points)
		{
			free_points(&coords->points);
			return (NULL); // dela with this NULL
		}
		i++;
		points->next = NULL;
		points = points->next;
	}
	return (coords->points);
}

void	init_pointcoord(t_coords **coords, t_vars *vars)
{
	t_coords		*coord;
	unsigned int	i;

	i = 1;
	coord = *coords;
	while (coord)
	{
		free_points(&coord->points);
		coord->points = init_points(coord, vars->width / vars->x,
				vars->height / vars->y, i); // change to varialbes to use zoom
		coord = coord->next;
		i++;
	}
	move_picture(vars);
	init_isometrics(vars);
}

t_coords	*init_coords(t_coords **coords, char **data)
{
	t_coords	*new_coord;
	t_coords	*coord;

	coord = *coords;
	new_coord = (t_coords *)malloc(sizeof(t_coords));
	if (!new_coord)
	{
		perror("Failed to allocate memmory");
		free_coords(coords);
		return (NULL);
	}
	new_coord->coordinate = data;
	new_coord->points = NULL;
	new_coord->next = NULL;
	if (!*coords)
		*coords = new_coord;
	else
	{
		while (coord->next)
			coord = coord->next;
		coord->next = new_coord;
	}
	return (new_coord);
}

void	parse_coordinates(char *file_name, t_vars *vars)
{
	int			fd;
	char		*line;
	t_coords	*tmp;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening the coordinates file");
		exit(1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = init_coords (&vars->coords, ft_split(line, ' '));
		if (!ft_arraystrlen(tmp->coordinate))
			clear_exit(tmp->coordinate, 1); // check this exit
		if (ft_arraystrlen(tmp->coordinate) > vars->x)
			vars->x = ft_arraystrlen(tmp->coordinate);
		free(line);
		tmp = tmp->next;
		(vars->y)++;
	}
	close(fd);
}
