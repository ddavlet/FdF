/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:59:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 13:00:44 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int32_t	max(int32_t n1, int32_t n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}

int32_t	min(int32_t n1, int32_t n2)
{
	if (n1 < n2)
		return (n1);
	else
		return (n2);
}
