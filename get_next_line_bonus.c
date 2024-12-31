/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:28:39 by adias-do          #+#    #+#             */
/*   Updated: 2024/12/03 19:29:13 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char			*all_line[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	all_line[fd] = read_line(fd, all_line[fd]);
	if (!ft_strlen(all_line[fd]))
	{
		free(all_line[fd]);
		return (NULL);
	}
	line = ft_get_line(all_line[fd]);
	len_line = ft_strlen(line);
	c = ft_strlen(all_line[fd]) - len_line;
	temp = all_line[fd];
	all_line[fd] = ft_substr(all_line[fd], len_line - 1, c);
	free(temp);
	return (line);
}
