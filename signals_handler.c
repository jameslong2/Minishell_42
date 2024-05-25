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