/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjo <hyeonjo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:49:43 by hyeonjo           #+#    #+#             */
/*   Updated: 2023/04/27 13:00:24 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_first_arg(t_cmd_info *tmp, t_cmd_info **ptr, t_cmd_info **head)
{
	tmp = (*ptr)->next;
	tmp->prev = NULL;
	(*head)->cmd_and_av = ft_free((*head)->cmd_and_av);
	*head = ft_free((*head));
	*head = tmp;
	*ptr = tmp;
}

void	check_argument(t_cmd_info **cmd)
{
	t_cmd_info	*cur;
	t_cmd_info	*temp;

	cur = *cmd;
	temp = NULL;
	while (cur)
	{
		if (cur->prev == NULL && cur->next == NULL)
			return ;
		if (cur->ac == 0 && cur->prev == NULL && cur->pipe_flag == 0)
			set_first_arg(temp, &cur, cmd);
		else if (cur->ac == 0 && cur->pipe_flag == 0)
		{
			temp = cur->prev;
			temp->next = cur->next;
			cur->cmd_and_av = ft_free(cur->cmd_and_av);
			cur = ft_free(cur);
			cur = temp->next;
			if (cur)
				cur->prev = temp;
		}
		else
			cur = cur->next;
	}
}
