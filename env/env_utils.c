/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:16:32 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/13 15:59:34 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_key(char *key_value)
{
	char	*temp;
	size_t	len;
	size_t	i;

	len = 0;
	while (key_value[len] != '=' && key_value[len] != 0)
	{
		++len;
	}
	if (key_value[len] == '\0')
	{
        return (NULL);
    }
	temp = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		temp[i] = key_value[i];
		++i;
	}
	temp[i] = 0;
	return (temp);
}

char	*get_env_value(char *key_value)
{
	char	*temp;
	size_t	len;
	size_t	i;

	len = 0;
	while (key_value[len] != 0 && key_value[len] != '=')
	{
        ++key_value;
    }
	if (key_value[len] == 0)
	{
        return (NULL);
    }
	len = ft_strlen(++key_value);
	temp = (char *)ft_malloc(sizeof(char), len + 1);
	i = 0;
	while (i < len)
	{
		temp[i] = key_value[i];
		++i;
	}
	temp[i] = 0;
	return (temp);
}

t_env_info	*compare_env_key(t_env_info *env_head, char *key)
{
	t_env_info	*temp;

	temp = env_head;
	// while (cur->key != 0 && ft_strncmp(key, cur->key, ft_strlen(cur->key)))
	while (temp->env_key != 0 && ft_strncmp(key, temp->env_key, ft_strlen(key)))
	{
        temp = temp->next;
    }
	return (temp);
}

t_env_info	*new_env(char *key_value)
{
	t_env_info	*temp;

	temp = (t_env_info *)ft_malloc(sizeof(t_env_info), 1);
	if (key_value == NULL)
	{
		temp->next = NULL;
		temp->prev = NULL;
		temp->env_val = NULL;
		temp->env_key = NULL;
	}
	else
	{
		temp->env_key = get_env_key(key_value);
		if (temp->env_key == NULL)
			return (NULL);
		temp->env_val = get_env_value(key_value);
		if (temp->env_val == NULL)
			return (NULL);
		temp->next = NULL;
		temp->prev = NULL;
	}
	return (temp);
}

int	ft_env_init(t_env_info *cur, char **envp)
{
	size_t	i;
	t_env_info	*temp;

	i = 0;
	cur->env_key = get_env_key(envp[1]);
	if (cur->env_key == NULL)
		return (-1);
	cur->env_val = get_env_value(envp[1]);
	if (cur->env_val == NULL)
		return (-1);
	cur->next = 0;
	cur->prev = 0;
	while (envp[++i])
	{
		temp = new_env(envp[i]);
		if (temp == NULL)
			return (-1);
		cur->next = temp;
		temp->prev = cur;
		cur = cur->next;
	}
	temp = new_env(NULL);
	temp->prev = cur;
	cur->next = temp;
	return (0);
}