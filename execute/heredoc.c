/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:25:17 by dmin              #+#    #+#             */
/*   Updated: 2023/05/03 13:55:54 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	assign_data(char **tmp_file, t_cmd_info *cur)
{
	*tmp_file = get_tmp_file_name();
	cur->in_fd = ft_open(*tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cur->in_file_name = ft_strdup(*tmp_file);
}

static void	set_exit_code_do(t_cmd_info *cur, int i, int *e, t_env_info *env)
{
	*e = do_fork_heredoc(cur, i, env);
	g_exit_signal_code = *e;
}

int	heredoc(t_cmd_info *cmd, t_env_info *env)
{
	char		*tmp_file;
	int			idx;
	int			exit_code;
	t_cmd_info	*cur;

	tmp_file = NULL;
	exit_code = 0;
	while (1)
	{
		cur = cmd;
		idx = check_heredoc(cur);
		if (idx == -1)
			return (0);
		if (cur->in_fd > 0)
			ft_close(cur->in_fd);
		assign_data(&tmp_file, cur);
		set_exit_code_do(cur, idx, &exit_code, env);
		if (exit_code == EXIT_SUCCESS)
			cur->in_fd = ft_open(tmp_file, O_RDONLY, 0664);
		ft_free(tmp_file);
		ft_free(cur->in_file_name);
		if (exit_code == EXIT_FAILURE)
			return (-1);
	}
	return (exit_code);
}
