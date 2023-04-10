/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:57:55 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/07 15:47:40 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}

static size_t	ft_get_word_cnt(const char *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			++cnt;
			while (*s && *s != c)
				++s;
			if (!*s)
				break ;
		}
		++s;
	}
	return (cnt);
}

static size_t	ft_get_word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		++s;
		++i;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	word_len;
	size_t	i;

	if (!s)
		return (0);
	ret = (char **)ft_malloc(sizeof(char *), (ft_get_word_cnt(s, c) + 1));
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_len = ft_get_word_len(s, c);
			ret[i] = (char *)ft_malloc(sizeof(char), word_len + 1);
			ft_strlcpy(ret[i++], s, word_len + 1);
			s += word_len - 1;
		}
		++s;
	}
	ret[i] = 0;
	return (ret);
}
