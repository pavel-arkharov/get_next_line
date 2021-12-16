/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:35:06 by parkharo          #+#    #+#             */
/*   Updated: 2021/11/30 19:12:19 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "get_next_line.h"

char	*check_remainder(char *remainder, char **line)
{
	char	*newl;

	newl = NULL;
	if (remainder)
	{
		if ((newl = ft_strchr(remainder, '\n')))
		{
			*newl++ = '\0';
			*line = ft_strdup(remainder);
			ft_strcpy(remainder, newl);
		}
		else
		{
			*line = ft_strdup(remainder);
			ft_strclr(remainder);
		}
	}
	else
		*line = (char *)malloc(sizeof(char) * 1);
	return (newl);
}

int	get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*remainder;
	char		*tmp;
	char		*newl;
	int			bytes_read;

	newl = check_remainder(remainder, line);
	while ((!newl && (bytes_read = read(fd, buf ,BUFF_SIZE))))
	{
		buf[bytes_read] = '\0';
		if ((newl = ft_strchr(buf, '\n')))
		{
			*newl++ = '\0';
			remainder = ft_strdup(newl);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return (bytes_read || ft_strlen(remainder) || ft_strlen(*line))? 1 : 0;
}
