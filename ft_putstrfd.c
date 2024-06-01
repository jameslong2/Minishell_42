#include "minishell.h"

void	ft_putstrfd(int fd, char *s)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}
