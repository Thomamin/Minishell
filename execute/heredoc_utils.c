/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjo <hyeonjo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:53:41 by hyeonjo           #+#    #+#             */
/*   Updated: 2023/05/03 14:58:37 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_key_in_line(char *ptr)
{
	size_t	i;
	char	*key;

	i = 1;
	while (ft_isalnum(ptr[i]) || ptr[i] == '_')
		i++;
	key = (char *)ft_malloc(sizeof(char), i);
	i = 1;
	while (ft_isalnum(ptr[i]) || ptr[i] == '_')
	{
		key[i - 1] = ptr[i];
		i++;
	}
	key[i - 1] = '\0';
	return (key);
}

static size_t	get_line_length(char *src, t_env_info *env)
{
	size_t	i;
	size_t	length;
	char	*key;

	i = -1;
	length = 0;
	while (src[++i])
	{
		if (src[i] == '$' && (ft_isalnum(src[i + 1]) || src[i + 1] == '_'))
		{
			key = get_key_in_line(src + i);
			length += ft_strlen(ft_getenv(env, key));
			i += ft_strlen(key);
			free(key);
		}
		else
			length++;
	}
	return (length);
}

static void	substitute_envvar(char *v, size_t *i_v, char *l, size_t *i_l)
{
	if (!v)
		return ;
	while (v[++(*i_v)])
		l[++(*i_l)] = v[(*i_v)];
}

static char	*copy_with_subs(char *l, char *s, t_env_info *env)
{
	size_t	i_s;
	size_t	i_l;
	size_t	i_v;
	char	*k;
	char	*v;

	i_s = -1;
	i_l = -1;
	while (s[++i_s])
	{
		if (s[i_s] == '$' && (ft_isalnum(s[i_s + 1]) || s[i_s + 1] == '_'))
		{
			i_v = -1;
			k = get_key_in_line(s + i_s);
			v = ft_getenv(env, k);
			i_s += ft_strlen(k);
			free(k);
			substitute_envvar(v, &i_v, l, &i_l);
		}
		else
			l[++i_l] = s[i_s];
	}
	l[++i_l] = '\0';
	return (l);
}

char	*parse_dollar_sign(char *src, t_env_info *env)
{
	char	*line;
	size_t	length;

	length = get_line_length(src, env);
	line = (char *)ft_malloc(sizeof(char), length + 1);
	line = copy_with_subs(line, src, env);
	free(src);
	return (line);
}
