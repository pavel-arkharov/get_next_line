/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 20:34:48 by parkharo          #+#    #+#             */
/*   Updated: 2021/12/10 15:21:54 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/includes/libft.h"

static t_line	*new_entry(int fd)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->cache = ft_strnew(BUFF_SIZE);
	if (!(new->cache))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}


char	*check_cache(char **newline, char *cache)
{
	char	*str;

	*newline = ft_strchr(cache, '\n');
	if ((*newline))
	{
		str = ft_strsub(cache, 0, *newline - cache);
		ft_strcpy(cache, ++(*newline));
	}
	else
	{
		str = ft_strnew(ft_strlen(cache) + 1);
		ft_strcat(str, cache);
		ft_strclr(cache);
	}
	return (str);
}

static int	get_line(const int fd, char *cache, char **line)
{
	char	*newline;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];
	int		ret;

	ret = 1;
	newline = NULL;
	*line = check_cache(&newline, cache);
	while (!newline && ret)
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		newline = ft_strchr(buf, '\n');
		if (newline)
		{
			*newline++ = '\0';
			cache = ft_strdup(newline);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	if (ft_strlen(*line) || ft_strlen(cache) || ret)
		return (1);
	else
		return (0);
}

int	get_next_line(const int fd, char **line)
{
	static t_line	*head;
	t_line			*tmp;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	if (head == NULL)
		head = new_entry(fd);
	if (!head)
		return (-1);
	tmp = head;
	if (tmp->fd != fd)
	{
		while (tmp->next != NULL && tmp->fd != fd)
			tmp = tmp->next;
		if (tmp->fd != fd)
			tmp->next = new_entry(fd);
	}
	return (get_line(fd, tmp->cache, line));
}	
