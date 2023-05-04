/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:32:53 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 16:27:17 by hyeonjo          ###   ########.fr       */
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
		++len;
	if (key_value[len] == '\0')
		return (ft_strdup(key_value));
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
		++key_value;
	if (key_value[len] == 0)
		return (NULL);
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
		temp->next = NULL;
		temp->prev = NULL;
	}
	return (temp);
}

static int	make_env_list(t_env_info *temp, t_env_info **cur, char **envp)
{
	size_t	i;

	i = 1;
	while (envp[i])
	{
		temp = new_env(envp[i++]);
		if (temp == NULL)
			return (-1);
		temp->prev = *cur;
		(*cur)->next = temp;
		*cur = temp;
	}
	return (0);
}

int	initialize_env(t_env_info *cur, char **envp)
{
	t_env_info	*temp;

	temp = NULL;
	if (*envp)
	{
		cur->env_key = get_env_key(envp[0]);
		if (cur->env_key == NULL)
			return (-1);
		cur->env_val = get_env_value(envp[0]);
		if (cur->env_val == NULL)
			return (-1);
		if (make_env_list(temp, &cur, envp) == -1)
			return (-1);
		temp = new_env(NULL);
		temp->prev = cur;
		cur->next = temp;
	}
	else
	{
		cur->next = NULL;
		cur->prev = NULL;
		cur->env_key = NULL;
		cur->env_val = NULL;
	}
	return (0);
}
