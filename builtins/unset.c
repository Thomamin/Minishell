// unset.c

#include "../minishell.h"

int mini_unset(t_cmd_info *cmd, t_info_env *env)
{
	t_info_env	*temp;
	char		*key;
	int			i;
	
	temp = env;
	i = 1;
	while (cmd->cmd_and_av[i]) 
	{
		key = cmd->cmd_and_av[i];
		if (!ft_is_valid_identifier(key))
			return (1);
		//find the env variable
		while (temp->env_key != 0 && ft_strncmp(key, temp->env_key, ft_strlen(key)))
		{
			temp = temp->next;
		}
		if(temp)
		{ //delete the variable node and free the node
			temp->prev->next = temp->next;
			free(temp);
		}
		i++;
	}
	return (0);
}
