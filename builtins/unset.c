/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:30:30 by dmin              #+#    #+#             */
/*   Updated: 2023/04/29 20:09:49 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_env_node(t_env_info *env_node)
{
	free(env_node->env_key);
	free(env_node->env_val);
	env_node->env_key = NULL;
	env_node->env_val = NULL;
	if (env_node->prev && env_node)
		free(env_node);
}

static void	del_env_node(t_env_info *env_node)
{
	if (env_node && env_node->env_key)
	{
		if (env_node->prev)
		{
			env_node->prev->next = env_node->next;
			env_node->next->prev = env_node->prev;
			free_env_node(env_node);
		}
		else
		{
			if (env_node->next)
			{
				free(env_node->env_key);
				env_node->env_key = ft_strdup(env_node->next->env_key);
				free(env_node->env_val);
				env_node->env_val = ft_strdup(env_node->next->env_val);
				del_env_node(env_node->next);
			}
			else
				free_env_node(env_node);
		}
	}
}

int	mini_unset(t_cmd_info *cmd, t_env_info *env)
{
	t_env_info	*env_node;
	int			i;

	i = 1;
	while (cmd->cmd_and_av[i])
	{
		if (!ft_is_valid_identifier(cmd->cmd_and_av[i]))
		{
			print_quote_err3("unset", \
			cmd->cmd_and_av[i], "not a valid identifier");
			return (1);
		}
		env_node = compare_env_key(env, cmd->cmd_and_av[i++]);
		del_env_node(env_node);
	}
	return (0);
}
