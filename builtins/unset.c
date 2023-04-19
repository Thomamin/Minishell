/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:30:30 by dmin              #+#    #+#             */
/*   Updated: 2023/04/18 14:30:34 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_unset(t_cmd_info *cmd, t_env_info *env)
{
	t_env_info	*temp;
	char		*key;
	int			i;

	temp = env;
	i = 1;
	while (cmd->cmd_and_av[i])
	{
		key = cmd->cmd_and_av[i];
		if (!ft_is_valid_identifier(key))
			return (printstderr(ft_strjoin(ft_strjoin("unset: '", key), \
										"': not a valid identifier\n")));
		while (temp->env_key != 0 && \
							ft_strncmp(key, temp->env_key, ft_strlen(key)))
			temp = temp->next;
		if (temp)
			temp->prev->next = temp->next;
		i++;
	}
	return (0);
}
