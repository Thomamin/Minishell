/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:01:41 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/13 14:47:30 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_path(char **path)
{
	size_t	i;

	i = 0;
	while (path[i])
		free (path[i++]);
	free (path);
}

static char	*get_absolute_path(t_cmd_info *cmd, char *path_env)
{
	char	*ret;
	char	*slash;
	char	**path;
	int		i;

	i = 0;
	path = ft_split(path_env, ':');
	slash = ft_strjoin("/", cmd->cmd_and_av[0]);
	while (path[i])
	{
		ret = ft_strjoin(path[i], slash);
		if (is_exist_file(ret))
			break ;
		free(ret);
		++i;
	}
	free(slash);
	if (path[i] == NULL)
		ret = NULL;
	free_path(path);
	return (ret);
}

static int	check_relative(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (!ft_isalnum(str[i]))
	{
		if (str[i] == '.' || str[i] == '/')
			ret = 1;
		i++;
	}
	return (ret);
}

char	*get_cmd_path(t_cmd_info *cmd, t_env_info *info_env)
{
	char	*ret;
	char	*path_env;

	ret = NULL;
	path_env = ft_getenv(info_env, "PATH");
	if (check_relative(cmd->cmd_and_av[0]) && is_exist_file(cmd->cmd_and_av[0]))
		return (ft_strdup(cmd->cmd_and_av[0]));
	else if (path_env != NULL)
		ret = get_absolute_path(cmd, path_env);
	if (ret == NULL && is_exist_file(cmd->cmd_and_av[0]))
		return (ft_strdup(cmd->cmd_and_av[0]));
	return (ret);
}