#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	check_exists(char *name, char **env)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (env[i] != 0)
	{
		j = 0;
		count = 0;
		// cambiar a nuestro strlen
		while (name[j] != '\0' && env[i][j] != '=')
		{
			if (name[j] == env[i][j])
				count++;
			j++;
		}
		if (count != strlen(name))
			printf("%s\n", env[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	int i;
	int fd;

	fd = open(ENVS_R, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(fd, 1);
	i = 1;
	while (i < argc - 1)
		check_exists(argv[i++], env);
	close(fd);
	// el ultimo valor es el PID de la ALIENSHELL
	kill(atoi(argv[argc - 1]), SIGUSR1);
	return (0);
}