#include "minishell.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// corregir para que expanda el $? a la variable de *status_exit(-1)

char	*get_word(char *comm, int pos)
{
	char	*word;
	int		i;
	char	*res;

	i = 0; /*
		while(isspace(comm[pos]) == 1)
			pos++;
		while(comm[pos] == '"')
			pos++;*/
	while (comm[pos + i] != ' ' && comm[pos + i] != '\0')
		i++;
	word = malloc(i + 1 * sizeof(char));
	if (!word)
		return (NULL);
	strncpy(word, &comm[pos], i); // strdup(word, comm, pos, i);
	word[i] = '\0';
	//	printf("WORD: %s\n", word);
	res = check_command(comm, word, pos);
	return (res);
}

char	**list_commands(void)
{
	char	**arr;

	arr = malloc(7 * sizeof(char *));
	arr[0] = "echo";
	arr[1] = "export";
	arr[2] = "unset";
	arr[3] = "cd";
	arr[4] = "pwd";
	arr[5] = "$?";
	arr[6] = NULL;
	return (arr);
}

char	*command_path(int num)
{
	char	**arr;

	arr = malloc(7 * sizeof(char *));
	arr[0] = ECHO_R;
	arr[1] = EXP_R_S;
	arr[2] = UNS_R_S;
	arr[3] = CD_R_S;
	arr[4] = PWD_R_S;
	arr[5] = ft_itoa(*status_exit(-1));
	arr[6] = NULL;
	return (arr[num]);
}

char	*check_command(char *comm, char *word, int pos)
{
	int		j;
	char	**all_comms;
	char	*res;

	j = 0;
	all_comms = list_commands();
	while (j < 6)
	{
		if (strcmp(word, all_comms[j]) == 0)
		{
			res = replace2(comm, pos, word, command_path(j));
			//			free(all_comms);
			return (res);
		}
		j++;
	}
	//	free(all_comms);
	return (comm);
}

char	*replace2(char *comm, int pos, char *word, char *path)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = strlen(comm) + strlen(path) - strlen(word);
	res = malloc(len + 1 * sizeof(char));
	if (!res)
		return (NULL);
	res = strncpy(res, comm, pos);
	while (i < strlen(path))
	{
		res[pos + i] = path[i];
		i++;
	}
	while (pos + i + j < len)
	{
		res[pos + i + j] = comm[pos + strlen(word) + j];
		j++;
	}
	res[pos + i + j] = '\0';
	//	free(word);
	//	free(comm);
	return (res);
}

char	*builtin_replace(char *comm1)
{
	int		n;
	char	*comm;

	n = 0;
	comm = get_word(comm1, 0);
	n = 1;
	while (n < strlen(comm))
	{
		if (comm[n] == '"')
		{
			while (comm[n] != '"')
				n++;
		}
		if (comm[n] == '|')
		{
			//			printf("hi\n");
			comm = get_word(comm, n + 1);
		}
		n++;
	}
	return (comm);
}

/*int main()
{
	char *str = "echo horse"; //should print path_echo horse
	printf("%s\n", builtin_replace(str));

	char *str1 = "echohorse"; //should print echohorse
	printf("%s\n", builtin_replace(str1));

	char *str2 = "echo |unset     "; //should print path_echo | oye!
	printf("%s\n", builtin_replace(str2));
}*/
