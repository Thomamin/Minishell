//pwd.c

#include "../minishell.h"

int	mini_pwd(t_cmd_info *cmd, t_env_info *env)
{
	(void) cmd;
	(void) env;

	printf("%s\n",ft_getenv(env, "PWD"));
	return(0);
}