/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:18:27 by yogun             #+#    #+#             */
/*   Updated: 2023/01/06 15:28:48 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sub(char **full_str, char **line)
{
	char	*s;

	s = NULL;
	if (*full_str)
	{
		*line = *full_str;
		s = ft_strchr(*full_str, '\n');
		if (s)
		{
			s++;
			if (*s != '\0')
				*full_str = ft_strdup(s);
			else
				*full_str = NULL;
			*s = '\0';
		}
		else
			*full_str = NULL;
	}
	else
	{
		*line = (char *)malloc(sizeof(char) * 1);
		*line[0] = '\0';
	}
	return (s);
}

char	*ft_sub1(char **full_str, char **line, char **buf)
{
	char	*s;
	char	*tmp;

	s = ft_strchr(*buf, '\n');
	if (s)
	{
		s++;
		if (*s != '\0')
			*full_str = ft_strdup(s);
		*s = '\0';
	}
	tmp = *line;
	*line = ft_strjoin(*line, *buf);
	free(tmp);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			i;
	char		*s;
	static char	*full_str;
	char		*line;

	if (BUFFER_SIZE < 1 || read(fd, 0, 0) == -1 || fd < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	s = ft_sub(&full_str, &line);
	i = 1;
	while (!s && i)
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = '\0';
		s = ft_sub1(&full_str, &line, &buf);
	}
	free(buf);
	if (ft_strlen(line) > 0)
		return (line);
	free (line);
	return (NULL);
}
