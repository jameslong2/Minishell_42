#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv, char **env)
{
	int i;
	int fd;
	char ch;

	ch = 4;
	fd = open(CD_PWD_R, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(fd, &ch, 1);
	close(fd);
	// el ultimo valor es el PID de la ALIENSHELL
	kill(atoi(argv[argc - 1]), SIGUSR2);
	return (0);
}