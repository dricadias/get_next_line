/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:26:04 by adias-do          #+#    #+#             */
/*   Updated: 2024/12/04 17:15:57 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *all_line)
{
	int		c;
	char	*line;

	c = 0;
	if (all_line[c] == '\0' || !all_line)
		return (NULL);
	while (all_line[c] != '\0' && all_line[c] != '\n')
		c++;
	line = malloc((c + 2) * (sizeof(char)));
	if (!line)
		return (NULL);
	c = 0;
	while (all_line[c] != '\0' && all_line[c] != '\n')
	{
		line[c] = all_line[c];
		c++;
	}
	if (all_line[c] == '\n')
	{
		line[c] = all_line[c];
		c++;
	}
	line[c] = '\0';
	return (line);
}

char	*read_line(int fd, char *all_line)
{
	int		c;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buffer)
		return (NULL);
	c = 1;
	while (!ft_strchr(all_line, '\n') && c != 0)
	{
		c = read(fd, buffer, BUFFER_SIZE);
		if (c == -1)
		{
			free(all_line);
			free (buffer);
			return (NULL);
		}
		buffer[c] = '\0';
		all_line = ft_strjoin(all_line, buffer);
	}
	free(buffer);
	return (all_line);
}

char	*get_next_line(int fd)
{
	int					c;
	int					len_line;
	char				*line;
	char				*temp;
	static char			*all_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	all_line = read_line(fd, all_line);
	if (!ft_strlen(all_line))
	{
		free(all_line);
		return (NULL);
	}
	line = ft_get_line(all_line);
	len_line = ft_strlen(line);
	c = ft_strlen(all_line) - len_line;
	temp = all_line;
	all_line = ft_substr(all_line, len_line - 1, c);
	free(temp);
	return (line);
}
