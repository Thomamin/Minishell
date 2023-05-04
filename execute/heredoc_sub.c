/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjo <hyeonjo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:43:20 by hyeonjo           #+#    #+#             */
/*   Updated: 2023/05/03 13:35:14 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_heredoc(t_cmd_info *cmd)
{
	int			idx;
	const char	redir_h[3] = {-60, -60, '\0'};

	idx = 0;
	while (cmd->cmd_and_av[idx])
	{
		if (!ft_strcmp(cmd->cmd_and_av[idx], redir_h))
			break ;
		idx++;
	}
	if (cmd->cmd_and_av[idx] == NULL)
		return (-1);
	return (idx);
}

void	input_heredoc(t_cmd_info *cmd, int index_lim, t_env_info *env)
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
		line = parse_dollar_sign(line, env);
		ft_write(cmd->in_fd, line, ft_strlen(line));
		ft_write(cmd->in_fd, "\n", 1);
		free(line);
	}
}

int	wait_heredoc(pid_t pid)
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

int	do_fork_heredoc(t_cmd_info *cmd, int index_lim, t_env_info *env)
{
	pid_t		pid;
	int			ret;
	const char	redir_h[3] = {-60, -60, '\0'};

	set_signal(DEFAULT, READLINE);
	pid = fork();
	if (pid == 0)
	{
		input_heredoc(cmd, index_lim + 1, env);
		cmd->in_fd = ft_close(cmd->in_fd);
		exit (EXIT_SUCCESS);
	}
	else
	{
		set_signal(IGNORE, IGNORE);
		cmd->in_fd = ft_close(cmd->in_fd);
		ret = wait_heredoc(pid);
	}
	set_signal(READLINE, READLINE);
	trim_cmd_argv(cmd, redir_h, 2);
	return (ret);
}
