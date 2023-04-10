/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:54:59 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/10 11:38:46 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_tokenize_while_dollar(char str, char *new, t_info_env *head, int quotes)
{
	static char	*env;

	env = NULL;
	if (ft_isalnum(str) || str == '_')
		env = ft_join_ascii(env, str);
	else if (str == '?' && env == NULL) 
	{
		env = ft_itoa(g_exit_signal_code);
		new = ft_strjoin_free(new, env);
		env = ft_free(env);
	}
	else
	{
		if (env != NULL)
		{
			new = ft_strjoin_free(new, ft_getenv(head, env));
			if (!(str == '\"' && quotes != 1) && !(str == '\'' && quotes != 2))
				new = ft_join_ascii(new, str);
			env = ft_free(env);
			g_exit_signal_code = 0; 
		}
		else
			new = ft_join_ascii(new, '$'); 
	}
	return (new);
}

static char	*ft_tokenize_while_else(char c, char *new, int quotes)
{
	char	*ret;

	ret = NULL;
	if (c == -32)
		ret = ft_join_ascii(new, ' ');
	else if (!(c == '\"' && quotes != 1) && !(c == '\'' && quotes != 2)) 
		ret = ft_join_ascii(new, c);
	else
		return (new);
	return (ret);
}

static int	dollar_check(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '$')
		return (1);
	else
		return (0);
}

static char	*ft_tokenize_while(t_cmd_info *cmd, t_info_env *head, int i)
{
	char	*new;
	int		j;
	int		ch_quote;
	int		ch_dollar;

	new = NULL;
	j = 0;
	ch_quote = 0;
	ch_dollar = 0;
	while (j <= (int)ft_strlen(cmd->cmd_and_av[i])) 
	{
		ch_quote = set_quotes(cmd->cmd_and_av[i][j], ch_quote, cmd); 
		if (cmd->cmd_and_av[i][j] == '$' && ch_quote != 1 && ch_dollar == 0) 
			ch_dollar = 1;
		else if (ch_dollar == 1)
		{
			new = ft_tokenize_while_dollar(cmd->cmd_and_av[i][j], new, head, ch_quote);
			ch_dollar = dollar_check(cmd->cmd_and_av[i][j]); 
		}
		else
			new = ft_tokenize_while_else(cmd->cmd_and_av[i][j], new, ch_quote);
		j++;
	}
	return (new);
}

void	ft_tokenize(t_cmd_info *cmd, t_info_env *info_env)
{
	char	*new;
	int		i;
	
	while (cmd) 
	{
		i = 0;
		while (i < cmd->ac) 
		{
			new = ft_tokenize_while(cmd, info_env, i); 
			if (new == NULL && cmd->ft_dollar_flag)
				ft_del_argv(cmd, &i); 
			else
				ft_change_argv(cmd, new, i);
			i++;
		}
		cmd = cmd->next;
	}
}
