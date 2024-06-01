/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:51:15 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/29 15:02:59 by astoiano         ###   ########.fr       */
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
	int	i;
	int	fd;

	fd = open(ENVS_R, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	i = 1;
	while (*env != 0)
		ft_putstrfd(fd, *(env++));
	while (i < argc - 1)
		ft_putstrfd(fd, argv[i++]);
	close(fd);
	return (0);
}
