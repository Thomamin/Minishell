
#include "../minishell.h"

char	*ft_getenv(t_env_info *env_head, char *key)
{
	t_env_info	*cur;

	cur = compare_env_key(env_head, key);
	return (cur->env_val);
}

void	ft_setenv(t_env_info *env_head, char *key_value)
{
	t_env_info	*cur;
	char		*key;
	char		*val;

	key = get_env_key(key_value);
	val = get_env_value(key_value);

	cur = compare_env_key(env_head, key);
	if (!ft_strcmp(cur->env_key, key))  // id key로 기존 변수 찾은 경우
	{
		//환경변수 값 변경
		//free(&cur->env_val);
		cur->env_val = val;
	}
	else //주어진 id로 설정된 변수가 없는 경우
	{
		// 새 환경변수 추가
		cur->next = new_env(key_value);
		cur->next->prev = cur;
	}
}