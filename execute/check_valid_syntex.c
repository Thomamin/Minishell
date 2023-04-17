/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_syntex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:57:32 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/12 15:19:45 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_alone_pipe(t_cmd_info *cmd)
{
	if (cmd->ft_pipe_flag && cmd->ac == 0)
	{
		print_err1("syntax error near unexpected token `|'");
		g_exit_signal_code = 258;
		return (-1);
	}
	return (0);
}

static int	check_redirection_file(t_cmd_info *cmd, int i, int ret)
{
	const char	oc[2] = {-76, '\0'};
	const char	oa[3] = {-76, -76, '\0'};
	const char	ic[2] = {-74, '\0'};
	const char	ia[3] = {-74, -76, '\0'};

	if (cmd->ac == 0)
		return (0);
	while (i < cmd->ac)
	{
		if (!ft_strcmp(cmd->cmd_and_av[i], oc) || !ft_strcmp(cmd->cmd_and_av[i], oa))
			if (cmd->cmd_and_av[i + 1] == NULL || ft_strlen(cmd->cmd_and_av[i + 1]) == 0)
				ret = -1;
		if (!ft_strcmp(cmd->cmd_and_av[i], ic) || !ft_strcmp(cmd->cmd_and_av[i], ia))
			if (cmd->cmd_and_av[i + 1] == NULL || ft_strlen(cmd->cmd_and_av[i + 1]) == 0)
				ret = -1;
		if (ret == -1)
		{
			print_err1("syntax error near unexpected token `newline'");
			g_exit_signal_code = 258;
			return (-1);
		}
		++i;
	}
	return (0);
}

static int	check_empty_cmd(t_cmd_info *cmd)
{
	if (cmd->ft_dollar_flag == false && cmd->ac == 1 && \
			!ft_strcmp(cmd->cmd_and_av[0], ""))
	{
		print_err2("", "command not found");
		g_exit_signal_code = 127;
		return (-1);
	}
	return (0);
}

int	check_valid_syntax(t_cmd_info *cmd)
{
	t_cmd_info	*cur;

	cur = cmd;
	if (check_alone_pipe(cmd) == -1)
		return (-1);
	if (cur->ac == 0)
		return (-1);
	while (cur)
	{
		if (check_empty_cmd(cur) == -1)
			return (-1);
		else if (check_redirection_file(cur, 0, 0) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
