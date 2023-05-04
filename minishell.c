/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjo <hyeonjo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:09:42 by hyeonjo           #+#    #+#             */
/*   Updated: 2023/05/03 14:59:50 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_tcs(int argc, char **argv)
{
	struct termios	term_sig;

	if (argc != 1)
		exit_errno("argument input error", NULL, 126);
	tcgetattr(STDIN_FILENO, &term_sig);
	term_sig.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_sig);
	set_signal(READLINE, READLINE);
	g_exit_signal_code = 0;
	(void)argv;
}

static void	readline_loop(t_env_info *info_env)
{
	char		*input;
	t_cmd_info	*cmd;

	while (1)
	{
		input = readline("minishell $ ");
		if (!input)
			break ;
		if (*input != '\0')
			add_history(input);
		if (*input != '\0' && !ft_str_isspace(input))
		{
			cmd = initialize_cmd();
			parse(input, cmd);
			tokenize(cmd, info_env);
			check_argument(&cmd);
			execute(cmd, info_env);
			free_list(cmd);
		}
		free(input);
	}
}

static void	wrap_up_env_list(t_env_info *node)
{
	free(node->env_key);
	free(node->env_val);
	if (node->next)
	{
		node = node->next;
		while (node->next)
		{
			node = node->next;
			free(node->prev->env_key);
			free(node->prev->env_val);
			free(node->prev);
		}
		free(node);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term_sig;
	t_env_info		info_env;

	tcgetattr(STDIN_FILENO, &term_sig);
	initialize_tcs(argc, argv);
	initialize_env(&info_env, envp);
	readline_loop(&info_env);
	wrap_up_env_list(&info_env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_sig);
}
