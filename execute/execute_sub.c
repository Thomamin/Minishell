/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:17:50 by dmin              #+#    #+#             */
/*   Updated: 2023/05/03 13:35:20 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	initialize_heredoc(t_cmd_info *cmd, t_env_info *env)
{
	t_cmd_info	*cur;

	cur = cmd;
	while (cur)
	{
		if (heredoc(cur, env) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}

void	clear_cmd(t_cmd_info *cmd)
{
	t_cmd_info	*cur;

	cur = cmd;
	while (cur)
	{
		if (cur->fd[WRITE] > 0)
			ft_close(cur->fd[WRITE]);
		if (cur->in_fd > 0)
			ft_close(cur->in_fd);
		if (cur->out_fd > 0)
			ft_close(cur->out_fd);
		if (cur->command_path != NULL)
			cur->command_path = ft_free(cur->command_path);
		if (cur->in_file_name > 0)
			delete_tmp_file(cur->in_file_name);
		cur = cur->next;
	}
}
