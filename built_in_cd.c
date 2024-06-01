/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:02:35 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/28 22:31:18 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//extra libs

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		fd;
	char	*home;
	char	*og;

	fd = open(CD_PWD_R, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (argc > 1)
	{
		while (argv[1][0] != 0)
			write(fd, argv[1]++, 1);
	}
	else
	{
		home = getenv("HOME");
		while (home[0] != 0)
			write(fd, home++, 1);
	}
	close(fd);
	return (0);
}
