/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:56:00 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/29 01:07:46 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_comilla(char *comm, int pos)
{
	char	c;

	c = comm[pos];
	pos++;
	while (comm[pos] != c && comm[pos] != '\0')
		pos++;
	return (pos);
}

char	*get_word(char *comm, int pos)
{
	char	*word;
	int		i;
	char	*res;
	char	c;

	i = 0;
	while (comm[pos + i] == ' ')
		pos++;
	while (comm[pos + i] != ' ' && comm[pos + i] != '\0')
	{
		if (comm[pos + i] == 39 || comm[pos + i] == 34)
			i = skip_comilla(comm, pos + i);
		i++;
	}
	word = malloc(i + 1 * sizeof(char));
	if (!word)
		return (NULL);
	strncpy(word, &comm[pos], i); // strdup(word, comm, pos, i); //replace
	word[i] = '\0';
	res = check_command(comm, word, pos);
	free(word);
	return (res);
}

char	*check_command(char *comm, char *word, int pos)
{
	int		j;
	char	**all_comms;
	char	*res;

	j = 0;
	all_comms = list_commands();
	while (j < 5)
	{
		if (strcmp(word, all_comms[j]) == 0)
		{
			res = replace2(comm, pos, word, command_path(j));
			//free_array(all_comms, 4);
			return (res);
		}
		j++;
	}
	//free_array(all_comms, 4);
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
	//free(path);
	free(comm);
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
		if (comm[n] == 39 || comm[n] == 34)
			n = skip_comilla(comm, n);
		else if (comm[n] == '|')
			comm = get_word(comm, n + 1);
		n++;
	}
	return (comm);
}
