/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:30:09 by dmin              #+#    #+#             */
/*   Updated: 2023/04/18 14:30:14 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_swap_elements(t_env_info *el_a, t_env_info *el_b)
{
	t_env_info	tmp;

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
	if (cur_el == NULL || cur_el->next == NULL)
		return (list);
	ft_sort_list(cur_el->next);
	while (cur_el->next->env_key != NULL \
			&& (ft_strcmp(cur_el->env_key, cur_el->next->env_key) > 0))
	{
		ft_swap_elements(cur_el, cur_el->next);
		cur_el = cur_el->next;
	}
	return (list);
}

t_env_info	*mini_copy_list(t_env_info *src)
{
	t_env_info	*dst;
	t_env_info	*tmp;

	tmp = NULL;
	while (src != NULL)
	{
		dst = (t_env_info *)malloc(sizeof(t_env_info));
		if (!dst)
			return (NULL);
		dst->prev = tmp;
		dst->env_key = src->env_key;
		dst->env_val = src->env_val;
		src = src->next;
		tmp = dst;
	}
	dst->next = NULL;
	while (dst->prev)
	{
		dst->prev->next = dst;
		dst = dst->prev;
	}
	return (dst);
}

int	mini_print_sorted_ev(t_env_info *env)
{
	t_env_info	*cp_env;

	cp_env = mini_copy_list(env);
	if (!cp_env)
		return (1);
	ft_sort_list(cp_env);
	while (cp_env->env_key)
	{
		if (cp_env->env_val)
			printf("declare -x %s=\"%s\"\n", cp_env->env_key, cp_env->env_val);
		else
			printf("declare -x %s\n", cp_env->env_key);
		cp_env = cp_env->next;
	}
	return (0);
}

int	mini_export(t_cmd_info *cmd, t_env_info *env)
{
	int			i;
	t_env_info	*tmp;

	if (cmd_and_av_cnt(cmd->cmd_and_av) == 1)
		return (mini_print_sorted_ev(env));
	i = 1;
	while (cmd->cmd_and_av[i])
	{
		if (!ft_is_valid_identifier(cmd->cmd_and_av[i]))
			return (printstderr(ft_strjoin(ft_strjoin("export: `", \
			cmd->cmd_and_av[i]), "': not a valid identifier\n")));
		env = compare_env_key(env, get_env_key(cmd->cmd_and_av[i]));
		if (env->env_key)
			env->env_val = get_env_value(cmd->cmd_and_av[i]);
		else
		{
			if (env->prev) //끝 null node 이전 node가 있으면 
			{
				env->prev->next = new_env(cmd->cmd_and_av[i]);
				env->prev->next->next = env;
				env->prev->next->prev = env->prev;
				env->prev = env->prev->next;
			}
			else // null node만 있는 경우, node를 생성하여 값을 기존 null node로 옮기고 생성된 node값을 null로 set 
			{
				tmp = new_env(cmd->cmd_and_av[i]);
				env->env_key = tmp->env_key;
				env->env_val = tmp->env_val;
				tmp->prev = env;
				env->next = tmp;
				tmp->env_key = NULL;
				tmp->env_val = NULL;
			}
		}
		i++;
	}
	return (0);
}
