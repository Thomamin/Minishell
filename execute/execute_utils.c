/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:25:14 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 13:21:38 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_need_fork(t_cmd_info *cmd)
{
	if (cmd->prev != NULL)
		return (1);
	if (cmd->pipe_flag == true)
		return (1);
	if (cmd->in_fd != -2)
		return (1);
	if (cmd->out_fd != -2)
		return (1);
	if (!ft_strcmp(cmd->cmd_and_av[0], "cd"))
		return (0);
	if (!ft_strcmp(cmd->cmd_and_av[0], "export"))
		return (0);
	if (!ft_strcmp(cmd->cmd_and_av[0], "unset"))
		return (0);
	if (!ft_strcmp(cmd->cmd_and_av[0], "exit"))
		return (0);
	return (1);
}

void	restore_redirection_char(t_cmd_info *cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd->cmd_and_av[i])
	{
		j = 0;
		while (cmd->cmd_and_av[i][j])
		{
			if (cmd->cmd_and_av[i][j] == -60)
				cmd->cmd_and_av[i][j] = '<';
			else if (cmd->cmd_and_av[i][j] == -62)
				cmd->cmd_and_av[i][j] = '>';
			++j;
		}
		++i;
	}
}

char	**get_envp(t_env_info *head)
{
	int			i;
	int			size;
	char		*env_key;
	t_env_info	*tmp;
	char		**result;

	i = -1;
	size = 0;
	tmp = head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	result = malloc(sizeof(char *) * size);
	tmp = head;
	while (++i < size - 1)
	{
		env_key = ft_strjoin(tmp->env_key, "=");
		result[i] = ft_strjoin(env_key, tmp->env_val);
		tmp = tmp->next;
		free(env_key);
	}
	result[i] = NULL;
	return (result);
}

void	ft_execve(const char *file, char *const *argv, char *const *envp)
{
	if (execve(file, argv, envp) == -1)
		exit_errno("execve()", strerror(errno), 126);
	return ;
}
