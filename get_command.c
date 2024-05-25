#include "minishell.h"

int	check_exit(char *line)
{
	while (*line == ' ')
		line++;
	if (strncmp(line, "exit", 4) == 0 && (*(line + 4) == ' ' || !(*(line + 4))))
		// number codes?
		return (0);
	return (1);
}

char	*parse_line(char *line)
{
	if (check_single_quote(line) == 1)
		return ("syntax error: unclosed quote"); // new error message?
	line = check_dollar(line);
	line = builtin_replace(line); // comillas missing, leaks
	return (line);
}

int	check_single_quote(char *line)
{
	char	c;

	while (*line != '\0')
	{
		if (*line == 34 || *line == 39)
		{
			c = *line;
			line++;
			while (*line != c && *line != '\0')
				line++;
			if (*line == '\0')
				return (1);
		}
		line++;
	}
	return (0);
}

char	*check_dollar(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos] != '\0')
	{
		if (line[pos] == 39)
		{
			pos++;
			while (line[pos] != 39 && line[pos] != '\0')
				pos++;
		}
		else if (line[pos] == '$' && line[pos + 1] == '?')
			line = replace2(line, pos, "$?", ft_itoa(*status_exit(-1)));
		// insert string
		pos++;
	}
	return (line);
}
/*
char *expand_$(char *line, int pos)
{
	if(line[pos + 1] == '?')
	{
		if(line[pos + 2] == ' ' || line[pos + 2] == '\0')
		{
			if(pos == 0)
				return (line = replace2(line, pos, "$?", "whatever"));
			else if (line[pos - 1] == ' ')
				return(line = replace2(line, pos, "$?", "whatever_u_want"));
		}
	}
	return(line);
}*/

/*int main(int argc, char **argv, char **env)
{
	char *line;

	while(1)
	{
		line = readline("Alienshell>>");
		if (*line)
			add_history(line);
		if (check_exit(line) == 0)
			printf("horse exit\n"); //new exit function: clear history,
				free line
		line = parse_line(line);

		printf("%s\n", line);
	}

}*/
