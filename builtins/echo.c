/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:27:54 by dmin              #+#    #+#             */
/*   Updated: 2023/04/08 12:27:56 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../minishell.h"

int	mini_echo(t_cmd_info *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd_and_av[i])
	{
		printf(cmd->cmd_and_av[i]);
		if (cmd->cmd_and_av[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}