/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:56:53 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/28 21:56:55 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cd_script(char **env)
{
	if (access(CD_R_S, F_OK) == 0)
	{
		delete_file(env, CD_R_S);
		create_final_file(env, CD_R_S, CD_S);
	}
	else
		create_final_file(env, CD_R_S, CD_S);
}

void	create_pwd_script(char **env)
{
	if (access(PWD_R_S, F_OK) == 0)
	{
		delete_file(env, PWD_R_S);
		create_final_file(env, PWD_R_S, PWD_S);
	}
	else
		create_final_file(env, PWD_R_S, PWD_S);
}
