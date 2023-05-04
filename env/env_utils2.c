/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:32:24 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 12:19:56 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(t_env_info *env_head, char *key)
{
	t_env_info	*cur;

	cur = compare_env_key(env_head, key);
	if (!cur)
		return (NULL);
	return (cur->env_val);
}

t_env_info	*compare_env_key(t_env_info *env_head, char *key)
{
	t_env_info	*tmp;

	tmp = env_head;
	while (tmp && tmp->env_key && ft_strcmp(key, tmp->env_key))
		tmp = tmp->next;
	return (tmp);
}
