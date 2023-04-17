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
//printf("cur_el key: %s, next_el key: %s\n", cur_el->env_key, cur_el->next->env_key);
	ft_sort_list(cur_el->next);
//	while (cur_el->next != NULL && (ft_strcmp(cur_el->env_key, cur_el->next->env_key) > 0))
	while (cur_el->next->env_key != NULL && (ft_strcmp(cur_el->env_key, cur_el->next->env_key) > 0))
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
		copy_env = (t_env_info *)malloc(sizeof(t_env_info) * i);
		if (!copy_env)
			return (1);

		// i = 0;
		// tmp_env = copy_env;
		// while (i < sizeof(*copy_env) / sizeof(t_env_info))
		// {
		// 	if (i == 0)
		// 		(tmp_env + i)->prev = NULL;
		// 	else
		// 		(tmp_env + i)->prev = (tmp_env + i - 1);
		// 	if (i == sizeof(*copy_env) / sizeof(t_env_info) - 1)
		// 		(tmp_env + i)->next = NULL;
		// 	else
		// 		(tmp_env + i)->next = (tmp_env + i + 1);
		// 	i++;
		// } 

		tmp_env = copy_env;
		while (env != NULL)
		{
			tmp_env->env_key = env->env_key;
			tmp_env->env_val = env->env_val;
			tmp_env->next = env->next;
			tmp_env->prev = env->prev;
			env = env->next;
			tmp_env = tmp_env->next;
		}

		// list sort
		ft_sort_list(copy_env);

		//list print out
		tmp_env = copy_env;
		while (tmp_env->env_key)
		{
			printf("%s=%s\n", tmp_env->env_key, tmp_env->env_val);
			tmp_env = tmp_env->next;
		}
		free (copy_env);
	}
	else //argument 즉 설정할 환경변수가 "ABC=12345"과 같은 형식으로 있는 경우 
	{
		i = 1;
		while (cmd->cmd_and_av[i])
		{
			// identifier를 추출하여 identifier 기준에 맞는지 확인
			if (!ft_is_valid_identifier(get_env_key(cmd->cmd_and_av[i])))
				return(printstderr(ft_strjoin(ft_strjoin("export: '", get_env_key(cmd->cmd_and_av[i])), "'not a valid identifier\n")));		

			//find the env key
			tmp_env = compare_env_key(env, get_env_key(cmd->cmd_and_av[i]));
			if(tmp_env->env_key) // if the env key found
			{ //update the env value
				tmp_env->env_val = get_env_value(cmd->cmd_and_av[i]);
			}
			else // if the env not exists
			{
				// t_env_info 구조체 생성하여 env list에 add <- 현재 list 운용체계에 따르면 last null env node 앞에 insert 
				tmp_env->prev->next = new_env(cmd->cmd_and_av[i]); 
				tmp_env->prev->next->next = tmp_env;
				tmp_env->prev->next->prev = tmp_env->prev;
				tmp_env->prev = tmp_env->prev->next;
			}
			i++;
		}
	}
	return (0);
}
