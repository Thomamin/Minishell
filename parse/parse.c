/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:44:06 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/13 14:47:29 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*in_pipe(char *str, int *ch_pipe, t_cmd_info **cmd, t_cmd_info *next) 
{
	if (*ch_pipe == 1) 
		exit_errno("argv error", "||", 1);
	(*cmd)->ft_pipe_flag = true;
	(*cmd)->cmd_and_av = ft_split_arg(str, ' ', &((*cmd)->ac));
	next = ft_cmd_init(); 
	(*cmd)->next = next;
	next->prev = (*cmd);
	(*cmd) = next;
	str = ft_free(str);
	*ch_pipe = 1;
	return (str);
}

static char	*add_redirect_space(char *str, char *input, char c)
{
	if (c == '>')
	{
		input--;
		if (!(*input == '>' || *input == ' '))
			str = ft_join_ascii(str, ' ');
		input++;
		str = ft_join_ascii(str, -62);
		input++;
		if (!(*input == '>' || *input == ' '))
			str = ft_join_ascii(str, ' ');
	}
	else if (c == '<')
	{
		input--;
		if (!(*input == '<' || *input == ' '))
			str = ft_join_ascii(str, ' ');
		input++;
		str = ft_join_ascii(str, -60);
		input++;
		if (!(*input == '<' || *input == ' '))
			str = ft_join_ascii(str, ' ');
	}
	return (str);
}

static char	*out_pipe(char *str, int *ch_pipe, char *input, int ch_quote)
{
	if (ch_quote == 0 && (*input == ';' || *input == '\\'))
		exit_errno("symbol error", input, 1);
	else if (ch_quote != 0 && *input == ' ')
		str = ft_join_ascii(str, -32);
	else if (ch_quote == 0 && ft_isspace(*input))
		str = ft_join_ascii(str, ' ');
	else if ((*input == '>' || *input == '<') && ch_quote == 0)
		str = add_redirect_space(str, input, *input);
	else
	{
		str = ft_join_ascii(str, input[0]);
		*ch_pipe = 0;
	}
	return (str);
}

void	ft_parse(char *input, t_cmd_info *cmd)
{
	t_cmd_info	*next;
	char	*str;
	int		ch_quote;
	int		ch_pipe;

	next = NULL;
	str = NULL;
	ch_quote = 0;
	ch_pipe = 0;
	while (*input)
	{
		ch_quote = set_quotes(*input, ch_quote, cmd);
		if (*input == '|' && ch_quote == 0)
			str = in_pipe(str, &ch_pipe, &cmd, next);
		else
			str = out_pipe(str, &ch_pipe, input, ch_quote);
		input++;
	}
	if (ch_quote != 0)
		exit_errno("quotes error", NULL, 1);
	if (str != NULL)
	{
		cmd->cmd_and_av = ft_split_arg(str, ' ', &(cmd->ac));
		str = ft_free(str);
	}
}
