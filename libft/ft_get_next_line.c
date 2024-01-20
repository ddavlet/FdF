/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:18:02 by ddavlety          #+#    #+#             */
/*   Updated: 2024/01/09 19:31:20 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*nextline(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == '\n')
		return ((char *)&s[i]);
	return (NULL);
}

static char	*write_toremain(char *to_return)
{
	char	*ptr;
	size_t	i;

	i = 0;
	while (to_return[i] != '\n' && to_return[i] != '\0')
		i++;
	if (to_return[i] == 0 || to_return[1] == 0)
		return (NULL);
	ptr = ft_substr(to_return, i + 1, ft_strlen(to_return) - i);
	if (*ptr == 0)
	{
		free(ptr);
		ptr = NULL;
	}
	to_return[i + 1] = 0;
	return (ptr);
}

static char	*write_toreturn(int fd, char *to_remain, char *buffer)
{
	long	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(to_remain);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = 0;
		if (!to_remain)
			to_remain = ft_strdup("");
		tmp = to_remain;
		to_remain = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (nextline(buffer))
			break ;
	}
	return (to_remain);
}

char	*get_next_line(int fd)
{
	static char	*to_remain;
	char		*to_return;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(to_remain);
		free(buffer);
		to_remain = NULL;
		buffer = NULL;
		return (NULL);
	}
	to_return = write_toreturn(fd, to_remain, buffer);
	free(buffer);
	buffer = NULL;
	if (!to_return)
		return (NULL);
	to_remain = write_toremain(to_return);
	return (to_return);
}
