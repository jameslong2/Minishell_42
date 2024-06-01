/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:52:44 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/29 15:02:52 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //extra headers

int	check_exists(char *name, char **env, int fd)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (env[i] != 0)
	{
		j = 0;
		count = 0;
		while (name[j] != '\0' && env[i][j] != '=')
		{
			if (name[j] == env[i][j])
				count++;
			j++;
		}
		if (count != ft_strlen(name))
			ft_putstrfd(fd, env[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	fd;

	fd = open(ENVS_R, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	i = 1;
	while (i < argc - 1)
		check_exists(argv[i++], env, fd);
	close(fd);
	return (0);
}
