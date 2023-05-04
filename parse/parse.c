/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:27:14 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 13:20:08 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*in_pipe(char *str, int *ch_pipe, t_cmd_info **cmd, t_cmd_info *nxt)
{
	if (*ch_pipe == 1)
		exit_errno("argv error", "||", 1);
	(*cmd)->pipe_flag = true;
	(*cmd)->cmd_and_av = ft_split_arg(str, ' ', &((*cmd)->ac));
	nxt = initialize_cmd();
	(*cmd)->next = nxt;
	nxt->prev = (*cmd);
	(*cmd) = nxt;
	str = ft_free(str);
	*ch_pipe = 1;
	return (str);
}

static char	*add_redirect_space(char *str, char *input, char c, int idx)
{
	if (c == '>')
	{
		if (idx != 0)
		{
			if (!(*(input - 1) == '>' || *(input - 1) == ' '))
				str = ft_join_ascii(str, ' ');
		}
		str = ft_join_ascii(str, -62);
		if (!(*(input + 1) == '>' || *(input + 1) == ' '))
			str = ft_join_ascii(str, ' ');
	}
	else if (c == '<')
	{
		if (idx != 0)
		{
			if (!(*(input - 1) == '<' || *(input - 1) == ' '))
				str = ft_join_ascii(str, ' ');
		}
		str = ft_join_ascii(str, -60);
		if (!(*(input + 1) == '<' || *(input + 1) == ' '))
			str = ft_join_ascii(str, ' ');
	}
	return (str);
}

static char	*out_pipe(char *str, t_chs *ch, char *input, int idx)
{
	if (ch->quote == 0 && (*input == ';' || *input == '\\'))
		exit_errno("symbol error", input, 1);
	else if (ch->quote != 0 && *input == ' ')
		str = ft_join_ascii(str, -32);
	else if (ch->quote == 0 && ft_isspace(*input))
		str = ft_join_ascii(str, ' ');
	else if ((*input == '>' || *input == '<') && ch->quote == 0)
		str = add_redirect_space(str, input, *input, idx);
	else
	{
		str = ft_join_ascii(str, input[0]);
		ch->pipe = 0;
	}
	return (str);
}

static void	input_cmd_and_av(char *str, int ch_quote, t_cmd_info *cmd)
{
	if (ch_quote != 0)
		exit_errno("quotes error", NULL, 1);
	if (str != NULL)
	{
		cmd->cmd_and_av = ft_split_arg(str, ' ', &(cmd->ac));
		str = ft_free(str);
	}
}

void	parse(char *input, t_cmd_info *cmd)
{
	t_cmd_info	*next;
	char		*str;
	t_chs		ch;
	int			idx;

	next = NULL;
	str = NULL;
	ch.quote = 0;
	ch.pipe = 0;
	idx = -1;
	while (input[++idx])
	{
		ch.quote = set_quotes(input[idx], ch.quote, cmd);
		if (input[idx] == '|' && ch.quote == 0)
			str = in_pipe(str, &ch.pipe, &cmd, next);
		else
			str = out_pipe(str, &ch, input + idx, idx);
	}
	input_cmd_and_av(str, ch.quote, cmd);
}
