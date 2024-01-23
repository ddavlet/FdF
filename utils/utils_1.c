/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:59:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/23 17:21:00 by ddavlety         ###   ########.fr       */
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

uint32_t	limits(uint32_t num, uint32_t num2, uint32_t max)
{
	num = (uint32_t)((float)num / (float)num2) * (float)max;
	if (num < 300) // change to WIDTH && HEIGHT
		return (300);
	return (num);
}
