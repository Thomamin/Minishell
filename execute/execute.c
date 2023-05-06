/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:25:07 by dmin              #+#    #+#             */
/*   Updated: 2023/05/03 17:03:19 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	os_builtins(t_cmd_info *cmd, t_env_info *info_env)
{
	char	*env_path;
	char	**now_env;

	env_path = ft_getenv(info_env, "PATH");
	if (env_path == NULL && cmd->command_path == NULL)
	{
		print_err3(cmd->cmd_and_av[0], NULL, "No such file or directory");
		return (127);
	}
	if (env_path != NULL && !ft_strlen(env_path) && cmd->command_path == NULL)
	{
		print_err3(cmd->cmd_and_av[0], NULL, "No such file or directory");
		return (127);
	}
	if (cmd->command_path == NULL)
	{
		print_err3(cmd->cmd_and_av[0], NULL, "command not found");
		return (127);
	}
	now_env = get_envp(info_env);
	ft_execve(cmd->command_path, cmd->cmd_and_av, now_env);
	return (EXIT_FAILURE);
}

static int	execute_cmd(t_cmd_info *cmd, t_env_info *info_env)
{
	restore_redirection_char(cmd);
	if (!cmd->cmd_and_av[0])
		return (0);
	if (!ft_strcmp(cmd->cmd_and_av[0], "echo"))
		return (mini_echo(cmd, info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "cd"))
		return (mini_cd(cmd, info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "pwd"))
		return (mini_pwd(cmd, info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "export"))
		return (mini_export(cmd, info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "unset"))
		return (mini_unset(cmd, info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "env"))
		return (mini_env(cmd, info_env));
	if (!ft_strcmp(cmd->cmd_and_av[0], "exit"))
		return (mini_exit(cmd, info_env));
	return (os_builtins(cmd, info_env));
}

static void	do_fork_cmd(t_cmd_info *cmd, t_env_info *info_env)
{
	pid_t	pid;
	int		exit_code;

	set_signal(DEFAULT, DEFAULT);
	pid = ft_fork();
	if (pid == 0)
	{
		redirect(cmd);
		close_unused_fd(cmd, pid);
		exit_code = execute_cmd(cmd, info_env);
		exit(exit_code);
	}
	else
	{
		close_unused_fd(cmd, pid);
		set_signal(IGNORE, IGNORE);
	}
	return ;
}

static void	do_cmd(t_cmd_info *cmd, t_env_info *info_env)
{
	g_exit_signal_code = execute_cmd(cmd, info_env);
	close_unused_fd(cmd, 1);
}

void	execute(t_cmd_info *cmd_head, t_env_info *info_env)
{
	t_cmd_info	*cmd_cur;

	cmd_cur = cmd_head;
	if (check_valid_syntax(cmd_head) == -1)
		return (clear_cmd(cmd_head));
	if (initialize_heredoc(cmd_cur, info_env) == -1)
		return (clear_cmd(cmd_head));
	while (cmd_cur)
	{
		if (io_file_open(cmd_cur, info_env) == -1)
		{
			cmd_cur = cmd_cur->next;
			continue ;
		}
		if (is_need_fork(cmd_cur) == true)
			do_fork_cmd(cmd_cur, info_env);
		else
			do_cmd(cmd_cur, info_env);
		if (cmd_cur->prev && cmd_cur->prev->fd[READ] > 0)
			cmd_cur->prev->fd[READ] = ft_close(cmd_cur->prev->fd[READ]);
		cmd_cur = cmd_cur->next;
	}
	wait_child();
	set_signal(READLINE, READLINE);
	return (clear_cmd(cmd_head));
}
