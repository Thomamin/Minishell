/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:00:07 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/08 15:02:39 by hyyoo            ###   ########.fr       */
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
	if (s_int == IGN)
		signal(SIGINT, SIG_IGN);
	if (s_int == DFL)
		signal(SIGINT, SIG_DFL);
	if (s_int == SHE)
		signal(SIGINT, signal_handler);
	if (s_quit == IGN)
		signal(SIGQUIT, SIG_IGN);
	if (s_quit == DFL)
		signal(SIGQUIT, SIG_DFL);
	if (s_quit == SHE)
		signal(SIGQUIT, signal_handler);
}
