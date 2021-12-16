
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
	while ((i = (get_next_line(fd, &line))) != 0)
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
	fd = open("foo.txt", O_RDONLY);
	while ((i = (get_next_line(fd, &line))) != 0)
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