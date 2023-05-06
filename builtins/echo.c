/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:29:02 by dmin              #+#    #+#             */
/*   Updated: 2023/05/03 15:29:19 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_continuous_n(char *str)
{
	while (*(++str))
	{
		if (*str != 'n')
			return (0);
	}
	return (1);
}

static void	mini_echo_prt(t_cmd_info *cmd, int i, int print_new_line)
{
	while (cmd->cmd_and_av[i])
	{
		printf("%s", cmd->cmd_and_av[i]);
		if (cmd->cmd_and_av[i + 1])
			printf(" ");
		i++;
	}
	if (print_new_line)
		printf("\n");
	return ;
}

int	mini_echo(t_cmd_info *cmd, t_env_info *env)
{
	int	i;
	int	print_new_line;

	(void) env;
	i = 1;
	print_new_line = 1;
	if ((ft_strlen(cmd->cmd_and_av[1]) > 1 \
	&& !ft_strncmp(cmd->cmd_and_av[1], "-n", 2)))
	{
		if (ft_strlen(cmd->cmd_and_av[1]) > 2)
		{
			if (is_continuous_n(cmd->cmd_and_av[1]))
			{
				print_new_line = 0;
				i++;
			}
		}
		else
		{
			print_new_line = 0;
			i++;
		}
	}
	mini_echo_prt(cmd, i, print_new_line);
	return (0);
}
