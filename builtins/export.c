//export.c

#include "../minishell.h"

void	ft_swap_elements(t_env_info *el_a, t_env_info *el_b)
{
	t_env_info tmp;
	
	tmp.env_val = el_a->env_val;
	tmp.env_key = el_a->env_key;
	el_a->env_val = el_b->env_val;
	el_a->env_key = el_b->env_key;
	el_b->env_val = tmp.env_val;
	el_b->env_key = tmp.env_key;
}

t_env_info	*ft_sort_list(t_env_info *list)
{
	t_env_info	*cur_el;

	cur_el = list;
	if (cur_el->next == NULL)
		return (list);
	ft_sort_list(cur_el->next);
	while (cur_el->next != NULL && (cur_el->env_key - cur_el->next->env_key < 0))
	{
		ft_swap_elements(cur_el, cur_el->next);
		cur_el = cur_el->next;
	}
	return (list);
}

int	ft_c_position(char *str, char c)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if(*tmp == c)
			return (tmp - str);
		tmp++;
	}
	//못찾으면 -1 return
	return (-1);
}

int	mini_export(t_cmd_info *cmd, t_env_info *env)
{
	int			i;
	char		*key;
	char		*val;
	t_env_info	*tmp_env;

	tmp_env = env;
	if (cmd_and_av_cnt(cmd->cmd_and_av) == 1) //argument 없을 경우 환경변수들을 alphabet order 출력
	{
		t_env_info	*copy_env;
		int			i;

		// env list 복사
		i = 0;
		while (tmp_env)
		{
			tmp_env = tmp_env->next;
			i++;
		}
		copy_env = (t_env_info *)malloc(sizeof(t_env_info) * (i + 1));
		if (!copy_env)
			return (1);
		(copy_env + i)->next = NULL;
		tmp_env = env;
		while (env != NULL)
		{
			copy_env->env_key = env->env_key;
			copy_env->env_val = env->env_val;
			copy_env->next = env->next;
			copy_env->prev = env->prev;
			i++;
		}

		// list sort
		ft_sort_list(copy_env);

		//list print out
		tmp_env = copy_env;
		while (tmp_env)
		{
			printf("%s=%s\n", tmp_env->env_key, tmp_env->env_val);
			tmp_env = tmp_env->next;
		}
		free (copy_env);
	}
	else
	{
		i = 1;
		while (cmd->cmd_and_av[i])
		{
		// 문자열 중 처음 만나는 '='기준으로 identifier와 value로 나눔
			ft_strlcpy(key, cmd->cmd_and_av[i], ft_c_position(cmd->cmd_and_av[i], '='));
			ft_strlcpy(val, cmd->cmd_and_av[i] + ft_strlen(key), ft_strlen(cmd->cmd_and_av[i]) - ft_strlen(key) - 1);
			//argument_tokens 갯수가 2가 아닌 경우 
			// 각 argument들 'identifier=value'형태인지 검사 아닌 경우 'argument값: not a valid identifier' error stderr출력
			//idendifier는 alphabet이나 ‘_’ 가능. 실패시 error code를  exit_status에 반영

		
		// t_env_info 구조체 생성
		// key(identifier)와 value값 assign
		// env list에 add

			i++;
		}
	}

	return (0);
}
