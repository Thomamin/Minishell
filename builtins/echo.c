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
#include "minishell.h"

int	mini_echo(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->arguments[i] != NULL)
	{
		printf(cmd->arguments[i]);
		if (cmd->arguments[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}