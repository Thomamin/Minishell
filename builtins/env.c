/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:29:20 by dmin              #+#    #+#             */
/*   Updated: 2023/04/18 14:29:27 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_env(t_cmd_info *cmd, t_env_info *env)
{
	t_env_info	*temp;

	(void) cmd;
	temp = env;
	while (temp && temp->next && temp->env_val)
	{
		if (temp->env_val != NULL)
			printf("%s=%s\n", temp->env_key, temp->env_val);
		temp = temp->next;
	}
	return (0);
}
