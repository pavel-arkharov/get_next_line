/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:38:02 by parkharo          #+#    #+#             */
/*   Updated: 2021/12/13 15:44:23 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFF_SIZE 1
#define MAX_FD 4096

typedef	struct	s_linelist
{
	char				*cache;
	int					fd;
	struct	s_linelist	*next;
}			t_line;

int	get_next_line(const int fd, char **line);

#endif