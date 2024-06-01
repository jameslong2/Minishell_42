/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:58:36 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/28 22:45:04 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cd_or_pwd(int signal)
{
	int		fd;
	int		count_status[2];
	char	character;
	char	path[MAXPATHLEN];

	fd = open(CD_PWD_R, O_RDONLY);
	if (fd < 0)
	{
		return ;
	}
	count_status[1] = read(fd, &character, 1);
	count_status[0] = 0;
	if (character == 4)
	{
		close(fd);
		printf("%s\n", getcwd(path, MAXPATHLEN));
		return ;
	}
	while (count_status[1] > 0)
	{
		count_status[0]++;
		count_status[1] = read(fd, &character, 1);
	}
	close(fd);
	handle_cd(&count_status[0]);
}

void	handle_cd(int *count_status)
{
	char	*readbuffer;
	int		fd;
	int		status;

	fd = open(CD_PWD_R, O_RDONLY);
	readbuffer = (char *)malloc(count_status[0] + 1);
	read(fd, readbuffer, count_status[0]);
	readbuffer[count_status[0]] = '\0';
	close(fd);
	delete_file(our_envs(0, 0), CD_PWD_R);
	status = chdir(readbuffer);
	if (status != 0)
	{
		printf("Error al cambiar de ruta\n");//change error message
	}
}
