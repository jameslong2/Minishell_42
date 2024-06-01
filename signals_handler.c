/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiano <astoiano@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 21:49:25 by astoiano          #+#    #+#             */
/*   Updated: 2024/05/28 22:01:07 by astoiano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	default_sig(int sig)
{
	return ;
}

void	ctrl_c_handler(int sig)
{
	status_exit(1);
	exit(0);
}
