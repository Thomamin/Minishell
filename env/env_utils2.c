/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:32:24 by dmin              #+#    #+#             */
/*   Updated: 2023/04/18 14:32:29 by dmin             ###   ########.fr       */
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

void	ft_setenv(t_env_info *env_head, char *key_value)
{
	t_env_info	*cur;
	char		*key;
	char		*val;

	key = get_env_key(key_value);
	val = get_env_value(key_value);
	cur = compare_env_key(env_head, key);
	if (cur && !ft_strcmp(cur->env_key, key))  // id key로 기존 변수 찾은 경우
		cur->env_val = val;
	else //주어진 id로 설정된 변수가 없는 경우
	{
		cur = env_head;
		while (cur && cur->next && cur->env_key)
			cur = cur->next;
		cur->prev->next = new_env(key_value);
		cur->prev->next->next = cur;
		cur->prev->next->prev = cur->prev;
		cur->prev = cur->prev->next;
	}
}
