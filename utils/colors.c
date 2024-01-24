/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 08:36:57 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/24 11:48:33 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

uint32_t	create_rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	get_r(uint32_t trgb)
{
	return ((trgb >> 24) & 0xFF);
}

uint32_t	get_g(uint32_t trgb)
{
	return ((trgb >> 16) & 0xFF);
}

uint32_t	get_b(uint32_t trgb)
{
	return ((trgb >> 8) & 0xFF);
}

uint32_t	get_t(uint32_t trgb)
{
	return (trgb & 0xFF);
}
