#include "minishell.h"

void	delete_file(char **env, char *filename)
{
	int pid;
	int status;
	int pipes[2];
	int	i;
	char **input;

	i = 2;
	input = (char **)malloc(sizeof(char *) * 4);
	input[0] = ft_strjoin("/bin/bash", "");
	input[1] = ft_strjoin("-c", "");
	input[2] = ft_strjoin("rm -rf ", filename);
	input[3] = 0;
	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipes[1], 1);
		close(pipes[0]);
		close(pipes[1]);
		execve("/bin/bash", input, env);
	}
	else
	{
		close(pipes[0]);
		close(pipes[1]);
		waitpid(pid, &status, 0);
	}
	while (i >= 0)
		free(input[i--]);
	free(input);
}