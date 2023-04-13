//pwd.c

#include "../minishell.h"

int	mini_pwd(t_cmd_info *cmd, t_info_env *env)
{
	(void) cmd;
	(void) env;

	printf("%s\n",ft_getenv(env, "PWD"));
	return(0);
}