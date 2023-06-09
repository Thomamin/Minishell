/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:25:28 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 13:21:50 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redirect_pipe_in(t_cmd_info *cmd)
{
	if (cmd->prev == false)
		return ;
	return (ft_dup2(cmd->prev->fd[READ], STDIN_FILENO));
}

static void	redirect_pipe_out(t_cmd_info *cmd)
{
	if (cmd->pipe_flag == false)
		return ;
	return (ft_dup2(cmd->fd[WRITE], STDOUT_FILENO));
}

static void	redirect_infile(t_cmd_info *cmd)
{
	if (cmd->in_fd < 0)
		return ;
	return (ft_dup2(cmd->in_fd, STDIN_FILENO));
}

static void	redirect_outfile(t_cmd_info *cmd)
{
	if (cmd->out_fd < 0)
		return ;
	return (ft_dup2(cmd->out_fd, STDOUT_FILENO));
}

void	redirect(t_cmd_info *cmd)
{
	redirect_pipe_in(cmd);
	redirect_pipe_out(cmd);
	redirect_infile(cmd);
	redirect_outfile(cmd);
	return ;
}
