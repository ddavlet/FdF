/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:59:26 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/21 20:36:41 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

uint32_t	max(uint32_t n1, uint32_t n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}

uint32_t	min(uint32_t n1, uint32_t n2)
{
	if (n1 < n2)
		return (n1);
	else
		return (n2);
}
