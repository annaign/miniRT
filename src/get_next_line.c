/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 23:26:28 by pshagwel          #+#    #+#             */
/*   Updated: 2020/06/28 23:26:29 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	gnl_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

static char	*create_line(char **remains, char **line)
{
	char	*ptr;

	ptr = NULL;
	if (*remains)
	{
		if ((ptr = ft_strchr(*remains, '\n')))
		{
			*ptr++ = '\0';
			*line = ft_strdup(*remains);
			ft_memmove(*remains, ptr, ft_strlen(ptr) + 1);
		}
		else
		{
			*line = ft_strdup(*remains);
			gnl_free(remains);
		}
	}
	else
		*line = ft_strdup("");
	return (ptr);
}

static void	ft_strjoin_gnl(char **line, char const *buf)
{
	char	*new_line;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(*line);
	len2 = ft_strlen(buf);
	new_line = malloc(sizeof(char) * (len1 + len2 + 1));
	if (new_line)
	{
		i = -1;
		while (++i < len1)
			new_line[i] = line[0][i];
		i = -1;
		while (++i < len2)
			new_line[len1 + i] = buf[i];
		new_line[len1 + len2] = '\0';
	}
	free(*line);
	*line = new_line;
}

int			get_next_line(int fd, char **line)
{
	static char	*remains = NULL;
	char		*b;
	ssize_t		size;
	char		*ptr;

	if (!line || BUFFER_SIZE < 0 || (size = read(fd, &ptr, 0)) ||
		!(b = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	ptr = create_line(&remains, line);
	while (line && !ptr && (size = read(fd, b, BUFFER_SIZE)) && size != -1)
	{
		b[size] = '\0';
		if ((ptr = ft_strchr(b, '\n')))
		{
			*ptr = '\0';
			remains = ft_strdup(++ptr);
		}
		ft_strjoin_gnl(line, b);
	}
	if (!line || (size == -1 && remains))
		gnl_free(&remains);
	gnl_free(&b);
	if (!line || size == -1)
		return (-1);
	return (remains ? 1 : 0);
}
