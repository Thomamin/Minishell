/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:00:55 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/12 14:43:45 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_heredoc(t_cmd_info *cmd)
{
	int			idx;
	const char	redir_h[3] = {-74, -74, '\0'};

	idx = -1;
	while (cmd->cmd_and_av[++idx])
		if (!ft_strcmp(cmd->cmd_and_av[idx], redir_h))
			break ;
	if (cmd->cmd_and_av[idx] == NULL)
		return (-1);
	return (idx);
}

static void	input_heredoc(t_cmd_info *cmd, int index_lim)
{
	char	*line;
	char	*limiter;

	limiter = cmd->cmd_and_av[index_lim];
	while (1)
	{	
		line = readline("> ");
		if (line == NULL)
			break ;
		else if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_write(cmd->ft_in_files, line, ft_strlen(line));
		ft_write(cmd->ft_in_files, "\n", 1);
		free(line);
	}
}

static int	wait_heredoc(pid_t pid)
{
	int		status;
	int		signo;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		signo = WTERMSIG(status);
		if (signo == SIGINT)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	do_fork_heredoc(t_cmd_info *cmd, int index_lim)
{
	pid_t		pid;
	int			ret;
	const char	redir_h[3] = {-74, -74, '\0'};

	set_signal(DFL, SHE);
	pid = fork();
	if (pid == 0)
	{
		input_heredoc(cmd, index_lim + 1);
		cmd->ft_in_files = ft_close(cmd->ft_in_files);
		exit (EXIT_SUCCESS);
	}
	else
	{
		set_signal(IGN, IGN);
		cmd->ft_in_files = ft_close(cmd->ft_in_files);
		ret = wait_heredoc(pid);
	}
	set_signal(SHE, SHE);
	trim_cmd_argv(cmd, redir_h, 2);
	return (ret);
}

int	heredoc(t_cmd_info *cmd)
{
	char		*tmp_file;
	int			idx;
	int			exit_code;
	t_cmd_info		*cur;

	while (1)
	{
		cur = cmd;
		idx = check_heredoc(cur);
		if (idx == -1)
			return (0);
		if (cur->ft_in_files > 0)
			ft_close(cur->ft_in_files);
		tmp_file = get_tmp_file_name();
		cur->ft_in_files = ft_open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		exit_code = do_fork_heredoc(cur, idx);
		g_exit_signal_code = exit_code;
		if (exit_code == EXIT_SUCCESS)
			cur->ft_in_files = ft_open(tmp_file, O_RDONLY, 0664);
		free(tmp_file);
		if (exit_code == EXIT_FAILURE)
			return (-1);
	}
	return (exit_code);
}