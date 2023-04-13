//env.c


#include "../minishell.h"

int mini_env(t_cmd_info *cmd, t_info_env *env)
{
	t_info_env *temp;

	(void) cmd; //subject에서 no option, no argument라고 했으나 입력한 경우 error msg출력할지?
	
	temp = env;
	while (temp->env_key != 0)
	{
		printf("%s=%s\n",temp->env_key,temp->env_val);
		temp = temp->next;		
	}
	return (0);
}
