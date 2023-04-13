/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:01:33 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/12 14:33:06 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	trim_cmd_argv(t_cmd_info *cmd, const char *set, int size)
{
	int	i;
	int	tmp;
	int	tmp_argc;

	i = -1;
	tmp_argc = cmd->ac;
	while (++i < cmd->ac)
		if (!ft_strcmp(cmd->cmd_and_av[i], set))
			break ;
	if (i == cmd->ac)
		return ;
	tmp = i;
	cmd->ac -= size;
	while (size--)
	{
		free(cmd->cmd_and_av[i]);
		while (i < tmp_argc)
		{
			cmd->cmd_and_av[i] = cmd->cmd_and_av[i + 1];
			++i;
		}
		i = tmp;
	}
}

static void	infile_open(t_cmd_info *cmd)
{
	int			i;
	const char	redir_in[2] = {-74, '\0'};

	while (1)
	{
		i = -1;
		while (cmd->cmd_and_av[++i])
			if (!ft_strcmp(cmd->cmd_and_av[i], redir_in))
				break ;
		if (cmd->cmd_and_av[i] == NULL)
			break ;
		if (cmd->ft_in_files > 0)
			close(cmd->ft_in_files);
		cmd->ft_in_files = open(cmd->cmd_and_av[i + 1], O_RDONLY, 0644);
		if (cmd->ft_in_files == -1)
			print_err3(cmd->cmd_and_av[i + 1], NULL, "No such file or directory");
		trim_cmd_argv(cmd, redir_in, 2);
	}
	return ;
}

static void	outfile_open_trim(t_cmd_info *cmd, int i)
{
	int			o_flag;
	const char	r_o[2] = {-76, '\0'};
	const char	r_a[3] = {-76, -76, '\0'};

	if (ft_strcmp(cmd->cmd_and_av[i], r_o) == 0)
	{
		o_flag = O_WRONLY | O_CREAT | O_TRUNC;
		cmd->ft_out_files = ft_open(cmd->cmd_and_av[i + 1], o_flag, 0644);
		trim_cmd_argv(cmd, r_o, 2);
	}
	else if (ft_strcmp(cmd->cmd_and_av[i], r_a) == 0)
	{
		o_flag = O_WRONLY | O_CREAT | O_APPEND;
		cmd->ft_out_files = ft_open(cmd->cmd_and_av[i + 1], o_flag, 0644);
		trim_cmd_argv(cmd, r_a, 2);
	}
}

static void	outfile_open(t_cmd_info *cmd)
{
	int			i;
	const char	r_o[2] = {-76, '\0'};
	const char	r_a[3] = {-76, -76, '\0'};

	while (1)
	{
		i = -1;
		while (cmd->cmd_and_av[++i])
			if (!ft_strcmp(cmd->cmd_and_av[i], r_o) || !ft_strcmp(cmd->cmd_and_av[i], r_a))
				break ;
		if (cmd->cmd_and_av[i] == NULL)
			break ;
		if (cmd->ft_out_files > 0)
			close(cmd->ft_out_files);
		outfile_open_trim(cmd, i);
	}
}

int	io_file_open(t_cmd_info *cmd, t_env_info *info_env)
{
	ft_pipe(cmd->fd);
	infile_open(cmd);
	if (cmd->ft_in_files == -1)
	{
		g_exit_signal_code = EXIT_FAILURE;
		return (-1);
	}
	outfile_open(cmd);
	cmd->ft_command_path = get_cmd_path(cmd, info_env);
	return (0);
}