/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:28:42 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 19:02:24 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_dir(char *path, t_env_info *env)
{
	int		ret;
	char	buf[4096];
	char	*tmp_str;

	getcwd(buf, 4096);
	ret = chdir(path);
	if (ret == 0)
	{
		tmp_str = ft_strjoin("OLDPWD=", buf);
		set_env(env, tmp_str);
		free(tmp_str);
		getcwd(buf, 4096);
		tmp_str = ft_strjoin("PWD=", buf);
		set_env(env, tmp_str);
		free(tmp_str);
	}
	else if (ret == -1)
	{
		ret = 1;
		perror("cd");
	}
	return (ret);
}

static int	check_path(char *path, char *msg)
{
	if (!path)
	{
		print_err2("cd", msg);
		return (1);
	}
	return (0);
}

static int	cd_home_and_oldpwd(t_env_info *env, char **path)
{
	char	*home_path;
	char	*tmp;

	tmp = *path;
	if (!ft_strncmp(*path, "-", ft_strlen(*path)))
	{
		*path = ft_strdup(ft_getenv(env, "OLDPWD"));
		if (check_path(*path, "OLDPWD not set"))
			return (1);
		printf("%s\n", *path);
	}
	else if (!ft_strncmp(*path, "~", 1))
	{
		home_path = ft_getenv(env, "HOME");
		if (check_path(home_path, "HOME not set"))
			return (1);
		*path = ft_strjoin(home_path, *path + 1);
	}
	free(tmp);
	return (0);
}

static int	set_mini_cd_path(t_env_info *env, char *input)
{
	char	buf[4096];
	char	*tmp_str;
	char	*path;
	int		ret;

	ret = 0;
	path = ft_strdup(input);
	if ((!ft_strncmp(path, "~", 1) || !ft_strcmp(path, "-"))
		&& (cd_home_and_oldpwd(env, &path) == 1))
			ret = 1;
	else if (*path != '/')
	{
		getcwd(buf, 4096);
		tmp_str = ft_strjoin(buf, "/");
		free(path);
		path = ft_strjoin(tmp_str, input);
		free(tmp_str);
		ret = change_dir(path, env);
	}
	else
		ret = change_dir(path, env);
	free(path);
	return (ret);
}

int	mini_cd(t_cmd_info *cmd, t_env_info *env)
{
	char	*path;

	if (cmd_and_av_cnt(cmd->cmd_and_av) > 2)
	{
		print_err2("cd", "too many arguments");
		return (1);
	}
	else if (cmd_and_av_cnt(cmd->cmd_and_av) == 1)
	{
		path = ft_getenv(env, "HOME");
		if (!path)
		{
			print_err2("cd", "HOME not set");
			return (1);
		}
		return (change_dir(path, env));
	}
	else
		return (set_mini_cd_path(env, cmd->cmd_and_av[1]));
}
