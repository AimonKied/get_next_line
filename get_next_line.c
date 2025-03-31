/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:42:10 by swied             #+#    #+#             */
/*   Updated: 2025/03/31 16:49:23 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 100

char	*get_next_line(int fd)
{
	static char		*buff = NULL;
	char			*line;
	static size_t	bytes_read;
	size_t			j;
	static size_t	i = 0;

	if (fd < 0)
		return (NULL);
	if (i == 0)
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
	}
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (i < bytes_read && buff[i] != '\n')
	{
		line[j++] = buff[i++];
	}
	if (i < bytes_read && buff[i] == '\n')
		line[j++] = buff[i++];
	line[j] = '\0';
	if (i >= bytes_read)
	{
		free(buff);
		buff = NULL;
		i = 0;
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("textfile1.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
