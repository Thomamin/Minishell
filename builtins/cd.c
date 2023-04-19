/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:28:42 by dmin              #+#    #+#             */
/*   Updated: 2023/04/18 14:28:49 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_dir(char *path, t_env_info *env)
{
	int		ret;
	char	buf[4096];

	getcwd(buf, 4096);
	ret = chdir(path);
	if (ret == 0)
	{
		ft_setenv(env, ft_strjoin("OLDPWD=", ft_strdup(buf)));
		getcwd(buf, 4096);
		ft_setenv(env, ft_strjoin("PWD=", ft_strdup(buf)));
	}
	else if (ret == -1)
	{
		ret = 1;
		perror("cd");
	}
	return (ret);
}

int	set_mini_cd_path(t_env_info *env, char *path)
{
	char	buf[4096];

	if (!ft_strncmp(path, "-", ft_strlen(path)))
	{
		path = ft_getenv(env, "OLDPWD");
		if (!path)
			return (printstderr("cd: OLDPWD not set"));
		printf("%s\n", path);
	}
	else if (!ft_strncmp(path, "~", ft_strlen(path)))
	{
		path = ft_getenv(env, "HOME");
		if (!path)
			return (printstderr("cd: HOME not set\n"));
	}
	else
	{
		if (*path != '/')
		{
			getcwd(buf, 4096);
			path = ft_strjoin(ft_strjoin(buf, "/"), path);
		}
	}
	return (change_dir(path, env));
}

int	mini_cd(t_cmd_info *cmd, t_env_info *env)
{
	char	*path;

	if (cmd_and_av_cnt(cmd->cmd_and_av) > 2)
		return (printstderr("cd: too many arguments\n"));
	else if (cmd_and_av_cnt(cmd->cmd_and_av) == 1)
	{
		path = ft_getenv(env, "HOME");
		if (!path)
			return (printstderr("cd: HOME not set\n"));
		return (change_dir(path, env));
	}
	else
		return (set_mini_cd_path(env, cmd->cmd_and_av[1]));
}
