/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:30:09 by dmin              #+#    #+#             */
/*   Updated: 2023/04/29 20:09:27 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	no_env_key(t_env_info *env, char *key_value)
{
	t_env_info	*tmp;

	if (env->prev)
	{
		env->prev->next = new_env(key_value);
		env->prev->next->next = env;
		env->prev->next->prev = env->prev;
		env->prev = env->prev->next;
	}
	else
	{
		tmp = new_env(key_value);
		env->env_key = tmp->env_key;
		env->env_val = tmp->env_val;
		tmp->prev = env;
		env->next = tmp;
		tmp->env_key = NULL;
		tmp->env_val = NULL;
	}
}

void	set_env(t_env_info *env, char *key_value)
{
	char		*key;
	char		*val;

	key = get_env_key(key_value);
	val = get_env_value(key_value);
	env = compare_env_key(env, key);
	if (env && env->env_key)
	{
		if (val && ft_strlen(val) > 0)
		{
			free(env->env_val);
			env->env_val = val;
		}
	}
	else
	{
		no_env_key(env, key_value);
		free(val);
	}
	free(key);
}

int	mini_export(t_cmd_info *cmd, t_env_info *env)
{
	int		i;

	if (cmd_and_av_cnt(cmd->cmd_and_av) == 1)
		return (mini_print_sorted_ev(env));
	i = 1;
	while (cmd->cmd_and_av[i])
	{
		if (!ft_is_valid_identifier(cmd->cmd_and_av[i]))
		{
			print_quote_err3("export", cmd->cmd_and_av[i], \
					"not a valid identifier");
			return (1);
		}
		set_env(env, cmd->cmd_and_av[i]);
		i++;
	}
	return (0);
}
