/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:58:09 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/29 00:37:31 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	free_array(char **input, int i)
{
	while (i >= 0)
		free(input[i--]);
	free(input);
}

char	**create_array(char *str)
{
	char	**input;

	input = (char **)malloc(sizeof(char *) * 4);
	input[0] = ft_strjoin("/bin/bash", "");
	input[1] = ft_strjoin("-c", "");
	input[2] = str;
	input[3] = 0;
	return (input);
}*/

void	delete_file(char **env, char *filename)
{
	int		pid;
	int		status;
	int		pipes[2];
	char	**input;

	input = create_array(ft_strjoin("rm -rf ", filename));
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
	free_array(input, 2);
}
