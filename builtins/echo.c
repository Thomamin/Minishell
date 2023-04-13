// echo.c

#include "../minishell.h"

int	mini_echo(t_cmd_info *cmd, t_env_info *env)
{
	int	i;

	(void) env;
	i = 1;
	while (cmd->cmd_and_av[i])
	{
		printf("%s", cmd->cmd_and_av[i]);
		if (cmd->cmd_and_av[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}
//리다이렉션 처리.
//환경변수
