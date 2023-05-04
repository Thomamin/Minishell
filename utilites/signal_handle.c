/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:28:21 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 11:58:16 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig_number)
{
	if (sig_number == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig_number == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(int s_int, int s_quit)
{
	if (s_int == IGNORE)
		signal(SIGINT, SIG_IGN);
	if (s_int == DEFAULT)
		signal(SIGINT, SIG_DFL);
	if (s_int == READLINE)
		signal(SIGINT, signal_handler);
	if (s_quit == IGNORE)
		signal(SIGQUIT, SIG_IGN);
	if (s_quit == DEFAULT)
		signal(SIGQUIT, SIG_DFL);
	if (s_quit == READLINE)
		signal(SIGQUIT, signal_handler);
}
