#include "minishell.h"

char	**list_commands(void)
{
	char	**arr;

	arr = malloc(6 * sizeof(char *));
	arr[0] = "echo";
	arr[1] = "export";
	arr[2] = "unset";
	arr[3] = "cd";
	arr[4] = "pwd";
	arr[5] = NULL;
	return (arr);
}

char	*command_path(int num)
{
	char	**arr;

	arr = malloc(6 * sizeof(char *));
	arr[0] = ECHO_R;
	arr[1] = EXP_R_S;
	arr[2] = UNS_R_S;
	arr[3] = CD_R_S;
	arr[4] = PWD_R_S;
	arr[5] = NULL;
	return (arr[num]);
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
}

void	free_array(char **input, int i)
{
	while (i >= 0)
		free(input[i--]);
	free(input);
}
