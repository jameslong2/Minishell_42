/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:54:58 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/29 15:43:14 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*status_exit(int new_status)
{
	static int	stat;

	stat = 0;
	if (new_status >= 0)
	{
		stat = new_status % 255;
	}
	return (&stat);
}

char	*unique_file_name(void)
{
	static char	name[FILENAME_MAX];

	return (&name[0]);
}

void	create_unique_name(char **env)
{
	int		pid;
	int		status;
	int		readammount;
	int		pipes[2];
	char	*input[] = {"/bin/bash", "-c", TIMESTAMP, 0};

	// hacer que el input sea un double pointer **
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
		readammount = read(pipes[0], unique_file_name(), FILENAME_MAX);
		close(pipes[0]);
		close(pipes[1]);
		unique_file_name()[readammount] = '\0';
		waitpid(pid, &status, 0);
	}
}

void	execute(char **env, char *full_command_line)
{
	int		pid;
	int		status;
	int		pipes[2];	
	char	**input; // hacer que el input sea un double pointer **

	input = (char **)malloc(sizeof(char *) * 3);
	input[0] = EXEC_R_S;
	input[1] = full_command_line;
	input[2] = 0; //into create array function
	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ctrl_c_handler);
		close(pipes[0]);
		close(pipes[1]);
		dup2(pipes[1], 1);
		execve(input[0], input, env);
	}
	else
	{
		close(pipes[0]);
		close(pipes[1]);
		waitpid(pid, &status, 0);
		status_exit(status);
	}
	free(input);
}
