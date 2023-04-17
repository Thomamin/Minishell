/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:03:42 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/13 14:48:23 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

t_cmd_info	*ft_cmd_init(void)
{
	t_cmd_info	*new;

	new = malloc(sizeof(t_cmd_info));
	new->fd[0] = -2;
	new->fd[1] = -2;
	new->ft_in_files = -2;
	new->ft_out_files = -2;
	new->ac = 0;
	new->ft_dollar_flag = false;
	new->ft_pipe_flag = false;
	new->ft_command_path = NULL;
	new->cmd_and_av = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_free_list(t_cmd_info *cmd)
{
	int		i;
	t_cmd_info	*temp;

	while (cmd)
	{
		i = 0;
		while (i < cmd->ac)
		{
			cmd->cmd_and_av[i] = ft_free(cmd->cmd_and_av[i]);
			i++;
		}
		cmd->cmd_and_av = ft_free(cmd->cmd_and_av);
		temp = cmd;
		cmd = cmd->next;
		temp = ft_free(temp);
	}
}
