/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:29:02 by dmin              #+#    #+#             */
/*   Updated: 2023/04/18 14:29:07 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_echo(t_cmd_info *cmd, t_env_info *env)
{
	int	i;
	int	print_new_line;

	(void) env;
	i = 1;
	print_new_line = 1;
	if (cmd->cmd_and_av[1] != NULL && !ft_strncmp(cmd->cmd_and_av[1], "-n", 2))
	{
		print_new_line = 0;
		i++;
	}
	while (cmd->cmd_and_av[i])
	{
		printf("%s", cmd->cmd_and_av[i]);
		if (cmd->cmd_and_av[i + 1])
			printf(" ");
		i++;
	}
	if (print_new_line)
		printf("\n");
	return (0);
}
//리다이렉션 처리.
//환경변수
