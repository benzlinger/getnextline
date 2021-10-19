/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btenzlin <btenzlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:26:27 by btenzlin          #+#    #+#             */
/*   Updated: 2021/09/10 12:40:09 by btenzlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*move_to_next(char *str, int start)
{
	char	*s;
	int		count;

	count = 0;
	if (!str || !str[count] || !str[start])
	{
		free(str);
		return (0);
	}
	s = malloc(sizeof(char) * ((ft_strlen(str) - start) + 1));
	if (!s)
		return (0);
	count = 0;
	while (str[start] != '\0')
	{
		s[count] = str[start];
		count++;
		start++;
	}
	s[count] = '\0';
	free(str);
	return (s);
}

int	size_line(char *save)
{
	int	count;

	count = 0;
	while (save[count] != '\n' && save[count] != '\0')
		count++;
	if (save[count] == '\n')
		count++;
	return (count);
}

char	*gnl_helper(char *save, char *buf, int fd, int size)
{
	while (size != 0 && !is_eol(save))
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
		{
			free(buf);
			return (0);
		}
		buf[size] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save[10240];
	char		*line;
	int			size;
	int			count;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	size = 1;
	save[fd] = gnl_helper(save[fd], buf, fd, size);
	if (!save[fd])
		return (0);
	count = size_line(save[fd]);
	line = ft_substr(save[fd], 0, count);
	save[fd] = move_to_next(save[fd], count);
	return (line);
}
