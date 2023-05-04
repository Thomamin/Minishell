/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjo <hyeonjo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:36:06 by hyeonjo           #+#    #+#             */
/*   Updated: 2023/04/27 19:04:42 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_swap_elements(t_env_info *el_a, t_env_info *el_b)
{
	t_env_info	tmp;

	tmp.env_val = el_a->env_val;
	tmp.env_key = el_a->env_key;
	el_a->env_val = el_b->env_val;
	el_a->env_key = el_b->env_key;
	el_b->env_val = tmp.env_val;
	el_b->env_key = tmp.env_key;
}

static t_env_info	*ft_sort_list(t_env_info *list)
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

static t_env_info	*mini_copy_list(t_env_info *src)
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

static void	free_env_list(t_env_info *env)
{
	t_env_info	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env);
		env = tmp;
	}
}

int	mini_print_sorted_ev(t_env_info *env)
{
	t_env_info	*cp_env;
	t_env_info	*tmp;

	cp_env = mini_copy_list(env);
	tmp = cp_env;
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
	free_env_list(tmp);
	return (0);
}
