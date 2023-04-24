
#include "../minishell.h"

void	close_unused_fd(t_cmd_info *cmd, pid_t pid)
{
	if (pid == 0)
	{
		if (cmd->fd[READ] != -2)
			cmd->fd[READ] = ft_close(cmd->fd[READ]);
	}
	else
	{
		if (cmd->fd[WRITE] != -2)
			cmd->fd[WRITE] = ft_close(cmd->fd[WRITE]);
	}
	return ;
}