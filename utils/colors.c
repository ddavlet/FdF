/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 08:36:57 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/16 14:40:49 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int32_t	create_trgb(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	get_r(int32_t trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int32_t	get_g(int32_t trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int32_t	get_b(int32_t trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int32_t	get_t(int32_t trgb)
{
	return (trgb & 0xFF);
}
