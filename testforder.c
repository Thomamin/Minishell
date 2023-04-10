#include "minishell.h"

void print_checker(t_cmd_info *cmd, t_info_env *env)
{
	t_cmd_info	*cur;
	t_info_env 	*env_cur;
	int			i;

	cur = cmd;
	while (cur)
	{
		i = 0;
		if (cur->cmd_and_av[i])
		{
			while (cur->cmd_and_av[i])
			{
				printf("i == %d, value == %s\n", i, cur->cmd_and_av[i]);
				i++;
			}
		}
		cur = cur->next;
	}
	// env_cur = env;
	
	// while (env_cur)
	// {
	// 	if (!ft_strcmp(env_cur->env_key, "USER") && env_cur->env_val)
	// 	{
	// 			printf("env_key == %s\n", env_cur->env_key);
	// 			printf("env_val == %s\n", env_cur->env_val);
	// 			printf("----------------------------------\n");
	// 	}
	// 	env_cur = env_cur->next;
	// }
}
