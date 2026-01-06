/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olunichk <olunichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 17:28:59 by olunichk          #+#    #+#             */
/*   Updated: 2026/01/06 15:59:47 by olunichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_to_remainder(int fd, char *remainder)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(remainder), NULL);
	bytes_read = 1;
	while (!ft_strchr(remainder, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(remainder), NULL);
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin_free(remainder, buffer);
		if (!tmp)
			return (free(buffer), NULL);
		remainder = tmp;
	}
	return (free(buffer), remainder);
}

static char	*fill_line(char *line, char *remainder)
{
	int	j;

	j = 0;
	while (remainder[j] && remainder[j] != '\n')
	{
		line[j] = remainder[j];
		j++;
	}
	if (remainder[j] == '\n')
	{
		line[j] = '\n';
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*extract_line(char *remainder)
{
	char	*line;
	int		i;

	i = 0;
	if (!remainder[i])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		line = malloc(sizeof(char) * (i + 2));
	else
		line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	return (fill_line(line, remainder));
}

static char	*update_remainder(char *remainder)
{
	char	*new_remainder;
	int		i;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = ft_substr(remainder, i + 1, ft_strlen(remainder + i + 1));
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	remainder[fd] = read_to_remainder(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	line = extract_line(remainder[fd]);
	if (!line)
	{
		free(remainder[fd]);
		remainder[fd] = NULL;
		return (NULL);
	}
	remainder[fd] = update_remainder(remainder[fd]);
	return (line);
}
