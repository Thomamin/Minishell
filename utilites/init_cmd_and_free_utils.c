/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_and_free_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:18:04 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 15:20:55 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

t_cmd_info	*initialize_cmd(void)
{
	t_cmd_info	*new;

	new = malloc(sizeof(t_cmd_info));
	new->fd[0] = -2;
	new->fd[1] = -2;
	new->in_fd = -2;
	new->out_fd = -2;
	new->ac = 0;
	new->dollar_flag = false;
	new->pipe_flag = false;
	new->in_file_name = NULL;
	new->command_path = NULL;
	new->cmd_and_av = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	free_list(t_cmd_info *cmd)
{
	int			i;
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
