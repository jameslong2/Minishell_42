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

	fd = open(ENVS_R, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(fd, 1);
	i = 1;
	while (*env != 0)
		printf("%s\n", *(env++));
	while (i < argc)
		printf("%s\n", argv[i++]);
	close(fd);
	// el ultimo valor es el PID de la ALIENSHELL
	kill(atoi(argv[argc - 1]), SIGUSR1);
	return (0);
}