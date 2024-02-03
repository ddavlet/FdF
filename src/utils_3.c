/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:58:41 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/03 13:00:24 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	clean_pixel(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (!img)
		ft_putendl_fd("Image does not exist", 2);
	if (!(x < img->width))
	{
		ft_putendl_fd("Pixel is out of bounds (axes x)", 2);
		printf("iso_x: %u width: %u\n", x, img->width);
	}
	if (!(y < img->height))
	{
		ft_putendl_fd("Pixel is out of bounds (axes y)", 2);
		printf("iso_y: %u height: %u\n", y, img->height);
	}
	pixelstart = &img->pixels[(y * img->width + x) * BPP];
	*(pixelstart++) = (uint8_t)(0);
	*(pixelstart++) = (uint8_t)(0);
	*(pixelstart++) = (uint8_t)(0);
	*(pixelstart++) = (uint8_t)(0);
}
