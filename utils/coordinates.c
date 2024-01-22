/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:51:55 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/22 16:06:47 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
