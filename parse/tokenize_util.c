/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:55:16 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/10 11:17:35 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (s1);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)ft_malloc(sizeof(char), (s1_len + s2_len + 1));
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(ret + s1_len, s2, s2_len + 1);
	free(s1);
	return (ret);
}

void	ft_del_argv(t_cmd_info *cmd, int *i)
{
	int		temp;

	temp = *i;
	cmd->cmd_and_av[temp] = ft_free(cmd->cmd_and_av[temp]);
	while (temp < cmd->ac - 1)
	{
		cmd->cmd_and_av[temp] = cmd->cmd_and_av[temp + 1];
		temp++;
	}
	*i = *i - 1;
	cmd->ac = cmd->ac - 1;
	cmd->ft_dollar_flag = false;
	cmd->cmd_and_av[temp] = 0;
}

void	ft_change_argv(t_cmd_info *cmd, char *new, int i)
{
	if (new == NULL)
		new = ft_strdup("");
	cmd->cmd_and_av[i] = ft_free(cmd->cmd_and_av[i]);
	cmd->cmd_and_av[i] = new;
}
