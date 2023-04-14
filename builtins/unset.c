// unset.c

#include "../minishell.h"

int mini_unset(t_cmd_info *cmd, t_env_info *env)
{
	t_env_info	*temp;
	char		*key;
	int			i;
	
	temp = env;
	i = 1;
	while (cmd->cmd_and_av[i]) 
	{
		key = cmd->cmd_and_av[i];
		if (!ft_is_valid_identifier(key))
			return (printstderr(ft_strjoin(ft_strjoin("unset: '", key),"': not a valid identifier\n")));
		//find the env variable
		while (temp->env_key != 0 && ft_strncmp(key, temp->env_key, ft_strlen(key)))
			temp = temp->next;
		if(temp)
		{ //delete the variable node and free the node
			temp->prev->next = temp->next;
//			free(temp->env_key);
//			free(temp->env_val);
//			free(temp);
		}
		i++;
	}
	return (0);
}
