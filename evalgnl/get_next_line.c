/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:10:23 by parkharo          #+#    #+#             */
/*   Updated: 2021/12/16 13:58:22 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_cache(char *cache, char **line)
{
	char	*newline;

	newline = NULL;
	if (cache)
	{
		newline = ft_strchr(cache, '\n');
		if (!newline)
		{
			*line = ft_strdup(cache);
			ft_strclr(cache);
		}
		else
		{
			*newline = '\0';
			newline++;
			*line = ft_strdup(cache);
			ft_strcpy(cache, newline);
		}
	}
	else
		*line = ft_strnew(1);
	return (newline);
}

static int	update_cache(char **newline, char **cache, char *buf)
{
	char	*tmp;

	if (!(ft_strchr(buf, '\n')))
		return (1);
	*newline = ft_strchr(buf, '\n');
	**newline = '\0';
	*newline += 1;
	tmp = *cache;
	*cache = ft_strdup(*newline);
	free(tmp);
	if (*cache == NULL)
		return (0);
	return (1);
}

static int	join_free(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free (tmp);
	if (!line)
		return (0);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*cache[MAX_FD];
	char		buf[BUFF_SIZE + 1];
	char		*newline;

	if (fd < 0 || !line)
		return (-1);
	ret = 1;
	newline = NULL;
	newline = extract_cache(cache[fd], line);
	while (ret && !newline)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (!(update_cache(&newline, &cache[fd], buf)))
			return (-1);
		if (!(join_free(line, buf)))
			return (-1);
	}
	if (ret || ft_strlen(*line))
		return (1);
	ft_strdel(&cache[fd]);
	return (0);
}
