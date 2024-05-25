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
}

void	full_exit(void)
{
	delete_files();
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	char *line;
	signal(SIGUSR2, get_cd_or_pwd);
	signal(SIGUSR1, cargar_envs);
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
		// execute(our_envs(0,0), line);
		delete_files();
	}
	printf("%s\n", OG_R);
	return (0);
}