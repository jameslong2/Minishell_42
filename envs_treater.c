#include "minishell.h"

char	**our_envs(char *file, char **init_envs)
{
	static char	**envs;

	envs = 0;
	// liberar memoria para evitar leaks
	if (init_envs == 0 && file != 0)
		envs = ft_split(file, '\n');
	else if (file == 0 && init_envs != 0)
		envs = init_envs;
	return (envs);
}

// para las env, utilizar SIGUSR1 para cargar las nuevas envs
void	cargar_envs(int signal)
{
	int fd;
	int count_status[2];
	char character;
	char *readbuffer;

	fd = open(ENVS_R, O_RDONLY);
	if (fd < 0)
	{
		printf("erroooooor\n");
		return ;
	}
	count_status[1] = read(fd, &character, 1);
	count_status[0] = 0;
	while (count_status[1] > 0)
	{
		count_status[0]++;
		count_status[1] = read(fd, &character, 1);
	}
	close(fd);
	fd = open(ENVS_R, O_RDONLY);
	readbuffer = (char *)malloc(count_status[0] + 1);
	read(fd, readbuffer, count_status[0]);
	readbuffer[count_status[0]] = '\0';
	our_envs(readbuffer, 0);
	close(fd);
	delete_file(our_envs(0, 0), ENVS_R);
}