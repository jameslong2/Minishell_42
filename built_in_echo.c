/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:03:17 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/28 22:31:38 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //no minishell.h include?

int	main(int argc, char **argv, char **env)
{
	int	flag;

	flag = 0;
	if (argc > 1)
	{
		if (argv[1][0] == '-' && argv[1][1] == 'n')
		{
			flag = 1;
			if (argc > 2)
				printf("%s", argv[2]);
		}
		else
			printf("%s", argv[1]);
	}
	if (flag == 0)
		printf("\n");
}
