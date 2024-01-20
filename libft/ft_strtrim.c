/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:54:44 by ddavlety          #+#    #+#             */
/*   Updated: 2023/11/20 13:08:52 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char const ch, char const *set)
{
	while (*set)
	{
		if (*set == ch)
			return (1);
		set++;
	}
	return (0);
}

static unsigned int	ft_index_base(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_check(s1[i], set))
			;
		else
			break ;
		i++;
	}
	return (i);
}

static unsigned int	ft_index_end(char const *s1, char const *set)
{
	unsigned int	j;

	j = ft_strlen(s1);
	if (j == 0)
		return (0);
	j--;
	while (j > 0)
	{
		if (ft_check(s1[j], set))
			;
		else
			break ;
		j--;
	}
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*ptr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = ft_index_base(s1, set);
	j = ft_index_end(s1, set);
	k = j - i + 1;
	if (!s1)
		return (0);
	else if (!set)
		return (ft_strdup(s1));
	ptr = ft_substr(s1, i, k);
	if (!ptr)
		return (0);
	return (ptr);
}
