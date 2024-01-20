/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:56:00 by ddavlety          #+#    #+#             */
/*   Updated: 2023/11/19 15:13:18 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_src;
	unsigned char	*ptr_dest;

	if (!dest && !src)
		return (dest);
	ptr_src = (unsigned char *)src;
	ptr_dest = (unsigned char *)dest;
	while (n != 0)
	{
		n--;
		ptr_dest[n] = ptr_src[n];
	}
	return (dest);
}
