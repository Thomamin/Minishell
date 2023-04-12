/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:28:38 by dmin              #+#    #+#             */
/*   Updated: 2023/04/08 12:28:42 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int mini_unset(t_cmd_info *cmd, t_info_env *env)
{
	t_info_env	*temp;
	char		*key;
	
	temp = env;
	key = cmd->cmd_and_av[1];
	//validate variable identifier - 첫글자는 alphabet or _ + 두번째 이후 alphanumeric or _
	
	//find the env variable
	while (temp->env_key != 0 && ft_strncmp(key, temp->env_key, ft_strlen(key)))
	{
        temp = temp->next;
    }
	if(temp)
	{ //delete the variable node and free the node
		temp->prev->next = temp->next;
		free(temp);
	}
	return (0);
}
