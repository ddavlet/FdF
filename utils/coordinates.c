/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:51:55 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/20 11:27:35 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_points(t_points *points)
{
	while (points)
	{
		free(points);
		points = points->next;
	}
}

t_points	*init_point(t_points **points, uint32_t x,
	uint32_t y, uint32_t z)
{
	t_points	*point;
	t_points	*last;

	point = (t_points *)malloc(sizeof(t_points));
	if (!point)
		return (NULL); //deal with this return
	point->x = x;
	point->y = y;
	point->z = z;
	point->iso_x = iso(x, y, z, 'x');
	point->iso_y = iso(x, y, z, 'y');
	point->color = 0xFFFFFF; //color
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

int	check_boundaries(t_vars *vars)
{
	t_coords	*coords;
	t_points	*tmp;

	coords = vars->coords;
	while (coords->next)
		coords = coords->next;
	tmp = coords->points;
	while (tmp)
	{
		if (tmp->iso_y >= vars->img->height
			|| tmp->iso_x >= vars->img->width)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_points	*init_points(t_coords *coords, uint32_t step_x,
		uint32_t step_y, unsigned int line)
{
	t_points		*points;
	unsigned int	i;

	i = 0;

	points = coords->points;
	free_points(coords->points);
	while ((coords->coordinate)[i])
	{
		points = init_point(&coords->points, step_x * (i + 1), step_y * line,
				(uint32_t)ft_atoi((coords->coordinate)[i]) * 6); // change z multiplier
		if (!points)
		{
			free_points(coords->points);
			return (NULL);
		}
		i++;
		points->next = NULL;
		points = points->next;
	}
	// if (check_boundaries(vars))
	// 	init_points(vars, step_x - 3, step_y - 3, line); //reallocating memory here
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
		coord->points = init_points(coord, vars->width / vars->x - vars->zoom, // change to varialbes to use zoom
				vars->height / vars->y - vars->zoom, i); // change to varialbes to use zoom
		coord = coord->next;
		i++;
	}
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
		free_points(coord->points);
		free(coord);
		coord = coord->next;
	}
}
