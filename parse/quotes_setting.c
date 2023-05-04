/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:27:17 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 13:01:55 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_quotes(char str, int ch_quotes, t_cmd_info *cmd)
{
	int	quote_state;

	if (str == '$')
		cmd->dollar_flag = true;
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
