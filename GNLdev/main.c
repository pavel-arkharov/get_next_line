/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 21:51:33 by parkharo          #+#    #+#             */
/*   Updated: 2021/12/16 14:07:13 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd;
	char *line;
	int i;

	fd = open("foo.txt", O_RDONLY);
	while ((i = (get_next_line(0, &line))) != 0)
	{
		ft_putstr("\nReturn vaue is: ");
		ft_putnbr(i);
		ft_putchar('\n');
		ft_putendl(line);
		//printf("\n\n Line address is: %p", &line);
		free(line);
	}
	free(line);
	close(fd);
	sleep(10);
	return (0);
}