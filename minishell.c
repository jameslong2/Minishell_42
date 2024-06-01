/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:59:25 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/29 16:46:10 by jaucarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_files(void)
{
	create_systax_file(our_envs(0, 0));
	create_unset_script(our_envs(0, 0));
	create_export_script(our_envs(0, 0));
	create_cd_script(our_envs(0, 0));
	create_pwd_script(our_envs(0, 0));
}

void	delete_files(void)
{
	delete_file(our_envs(0, 0), EXEC_R_S);
	delete_file(our_envs(0, 0), EXP_R_S);
	delete_file(our_envs(0, 0), UNS_R_S);
	delete_file(our_envs(0, 0), CD_R_S);
	delete_file(our_envs(0, 0), PWD_R_S);
	delete_file(our_envs(0, 0), ENVS_R);
	delete_file(our_envs(0, 0), CD_PWD_R);
}

void	full_exit(void)
{
	delete_files();
	exit(0);
}

void printenv(char **env)
{
	while (*env != 0)
		printf("%s\n",*(env++));
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	signal(SIGINT, default_sig);
	our_envs(0, env);
	while (1)
	{
		line = readline("Alienshell>>");
		if (line == 0)
			continue ;
		if (*line)
			add_history(line);
		if (check_exit(line) == 0)
			full_exit();
		line = parse_line(line);
		create_files();
		delete_file(our_envs(0, 0), ENVS_R);
		delete_file(our_envs(0, 0), CD_PWD_R);
		execute(our_envs(0, 0), line);
		get_cd_or_pwd(0);
		cargar_envs(0);
		delete_files();
	}
	return (0);
}
