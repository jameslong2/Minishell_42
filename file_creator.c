/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_creator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:57:35 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/28 21:57:43 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_final_file(char **env, char *filename, char *file_content)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(fd, file_content, ft_strlen(file_content));
	close(fd);
	only_exec_permissions(env, filename);
}

void	create_systax_file(char **env)
{
	long long	i;

	if (access(EXEC_R_S, F_OK) == 0)
	{
		delete_file(env, EXEC_R_S);
		create_final_file(env, EXEC_R_S, EXEC);
	}
	else
	{
		create_final_file(env, EXEC_R_S, EXEC);
	}
}

void	create_unset_script(char **env)
{
	if (access(UNS_R_S, F_OK) == 0)
	{
		delete_file(env, UNS_R_S);
		create_final_file(env, UNS_R_S, UNS_S);
	}
	else
		create_final_file(env, UNS_R_S, UNS_S);
}

void	create_export_script(char **env)
{
	if (access(EXP_R_S, F_OK) == 0)
	{
		delete_file(env, EXP_R_S);
		create_final_file(env, EXP_R_S, EXP_S);
	}
	else
		create_final_file(env, EXP_R_S, EXP_S);
}

void	only_exec_permissions(char **env, char *filename)
{
	int		pid;
	int		status;
	int		pipes[2];
	char	**input;

	input = create_array(ft_strjoin("chmod 555 ", filename));
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
