/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:29:57 by dmin              #+#    #+#             */
/*   Updated: 2023/04/18 14:30:00 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_exit(t_cmd_info *cmd, t_env_info *env)
{
	int		i;
	int		ret;

	(void) env;
	i = 0;
	ret = 0;
	if (cmd_and_av_cnt(cmd->cmd_and_av) > 2)
		return (printstderr("exit: too many arguments\n"));
	if (cmd_and_av_cnt(cmd->cmd_and_av) == 2)
	{
		while (*(cmd->cmd_and_av[1] + i))
		{
			if (!ft_isdigit(*(cmd->cmd_and_av[1] + i)))
			{
				print_err3("exit", (cmd->cmd_and_av[1] + i), \
					"numeric argument required");
				return (1);
			}
			i++;
		}
		ret = ft_atoi(cmd->cmd_and_av[1]);
	}	
	printf("exit\n");
	exit(ret);
}
