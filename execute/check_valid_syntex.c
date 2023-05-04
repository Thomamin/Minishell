/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_syntex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:24:48 by dmin              #+#    #+#             */
/*   Updated: 2023/04/29 20:10:30 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_alone_pipe(t_cmd_info *cmd)
{
	if (cmd->pipe_flag && cmd->ac == 0)
	{
		print_err1("syntax error near unexpected token `|'");
		g_exit_signal_code = 258;
		return (-1);
	}
	return (0);
}

static int	check_redirection_file(t_cmd_info *cmd, int i)
{
	const char	oc[2] = {-62, '\0'};
	const char	oa[3] = {-62, -62, '\0'};
	const char	ic[2] = {-60, '\0'};
	const char	ia[3] = {-60, -60, '\0'};

	if (cmd->ac == 0)
		return (0);
	while (i < cmd->ac)
	{
		if ((!ft_strcmp(cmd->cmd_and_av[i], oc) || \
				!ft_strcmp(cmd->cmd_and_av[i], oa) || \
				!ft_strcmp(cmd->cmd_and_av[i], ic) || \
				!ft_strcmp(cmd->cmd_and_av[i], ia)) && \
				(cmd->cmd_and_av[i + 1] == NULL || \
				ft_strlen(cmd->cmd_and_av[i + 1]) == 0))
		{
			print_err1("syntax error near unexpected token `newline'");
			g_exit_signal_code = 258;
			return (-1);
		}
		++i;
	}
	return (0);
}

int	is_directory(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

static int	check_empty_cmd(t_cmd_info *cmd)
{
	if (cmd->dollar_flag == false && cmd->ac == 1 && \
			!ft_strcmp(cmd->cmd_and_av[0], ""))
	{
		print_err2("", "command not found");
		g_exit_signal_code = 127;
		return (-1);
	}
	if (cmd->dollar_flag == false && cmd->ac == 1 && \
		(cmd->cmd_and_av[0][0] == '.' || cmd->cmd_and_av[0][0] == '/') && \
		is_directory(cmd->cmd_and_av[0]))
	{
		print_err2(cmd->cmd_and_av[0], "is a directory");
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
		else if (check_redirection_file(cur, 0) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
