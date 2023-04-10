
#include "../minishell.h"

char	*ft_getenv(t_info_env *env_head, char *key)
{
	t_info_env	*cur;

	cur = compare_env_key(env_head, key);
	return (cur->env_val);
}