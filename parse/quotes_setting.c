/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:44:43 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/10 11:17:34 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_quotes(char str, int ch_quotes, t_cmd_info *cmd)
{
	int	quote_state;

	if (str == '$')
		cmd->ft_dollar_flag = true;
	quote_state = ch_quotes;
	if (str == '\'')
	{
		if (ch_quotes == 1)
			quote_state = 0;
		else if (ch_quotes == 2)
			quote_state = 2;
		else
			quote_state = 1;
	}
	else if (str == '\"')
	{
		if (ch_quotes == 2)
			quote_state = 0;
		else if (ch_quotes == 1)
			quote_state = 1;
		else
			quote_state = 2;
	}
	return (quote_state);
}
