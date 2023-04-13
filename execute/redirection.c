/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:01:49 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/12 14:05:31 by youngjpa         ###   ########.fr       */
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
	if (cmd->ft_pipe_flag == false)
		return ;
	return (ft_dup2(cmd->fd[WRITE], STDOUT_FILENO));
}

static void	redirect_infile(t_cmd_info *cmd)
{
	if (cmd->ft_in_files < 0)
		return ;
	return (ft_dup2(cmd->ft_in_files, STDIN_FILENO));
}

static void	redirect_outfile(t_cmd_info *cmd)
{
	if (cmd->ft_out_files < 0)
		return ;
	return (ft_dup2(cmd->ft_out_files, STDOUT_FILENO));
}

void	redirect(t_cmd_info *cmd)
{
	redirect_pipe_in(cmd);
	redirect_pipe_out(cmd);
	redirect_infile(cmd);
	redirect_outfile(cmd);
	return ;
}