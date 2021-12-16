/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_with_lists.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:21:07 by parkharo          #+#    #+#             */
/*   Updated: 2021/12/13 15:39:28 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/includes/libft.h"

char	*extract_cache(char *cache, char **line)
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

int	join_free(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free (tmp);
	if (!line)
		return (0);
	return (1);
}

int	update_cache(char **newline, char **cache, char *buf)
{
	char	*tmp;

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

static t_line	*new_entry(int fd)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->cache = ft_strnew(0);
	if (!(new->cache))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

int	get_line(int fd, char **cache, char **line)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*newline;

	ret = 1;
	newline = NULL;
	newline = extract_cache(*cache, line);
	while (ret && !newline)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (ft_strchr(buf, '\n'))
			if (!(update_cache(&newline, cache, buf)))
				return (-1);
		if (!(join_free(line, buf)))
			return (-1);
	}
	if (ret || ft_strlen(*line))
		return (1);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static t_line	*head;
	t_line			*tmp;

	if (fd < 0 || !line)
		return (-1);
	if (!head)
		head = new_entry(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = new_entry(fd);
		tmp = tmp->next;
	}
	return (get_line(fd, &(tmp->cache), line));
}
