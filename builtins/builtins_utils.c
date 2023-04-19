/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:27:39 by dmin              #+#    #+#             */
/*   Updated: 2023/04/18 14:27:45 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_and_av_cnt(char **cmd_and_av)
{
	int	cnt;

	cnt = 0;
	while (cmd_and_av[cnt])
		cnt++;
	return (cnt);
}

int	printstderr(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	return (1);
}

int	ft_is_valid_identifier(char *identifier)
{
	int	i;

	if (!identifier || (!ft_isalpha(*identifier) && *identifier != '_'))
		return (0);
	i = 0;
	while (*identifier && *(identifier + i) != '=' && \
		(ft_isalnum(*(identifier + i)) || *(identifier + i) == '_'))
		i++;
	if (*(identifier + i) && *(identifier + i) != '=')
		return (0);
	return (1);
}
