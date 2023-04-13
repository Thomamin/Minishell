
#include "../minishell.h"

char	*ft_getenv(t_env_info *env_head, char *key)
{
	t_env_info	*cur;

	cur = compare_env_key(env_head, key);
	return (cur->env_val);
}