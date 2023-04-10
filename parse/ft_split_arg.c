/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:51:31 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/10 11:17:31 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*is_free(char **str, int str_index)
{
	int	i;

	i = 0;
	while (i < str_index)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int	get_word_cnt(char const *str, char c)
{
	size_t	count;
	int		checker;

	count = 0;
	checker = 1;
	while (*str != '\0' && *str == c)
		str++;
	while (*str)
	{
		if (checker == 1 && *str != c)
		{
			count++;
			checker = 0;
		}
		if (*str == c)
			checker = 1;
		str++;
	}
	return (count);
}

static char	**set_worddup(char const *s, char c, char **mem)
{
	size_t	word_length;
	int		i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		word_length = 0;
		while (s[word_length] && s[word_length] != c)
			word_length++;
		mem[i] = (char *)malloc(sizeof(char) * (word_length + 1));
		if (!mem[i])
			return (is_free(mem, i));
		ft_strlcpy(mem[i], s, word_length + 1);
		s = s + word_length;
		i++;
	}
	mem[i] = NULL;
	return (mem);
}

char	**ft_split_arg(char const *s, char c, int *argc)
{
	char	**new_mem;

	if (!s)
		return (NULL);
	new_mem = NULL;
	*argc = get_word_cnt(s, c);
	new_mem = (char **)malloc(sizeof(char *) * (*argc + 1));
	if (!new_mem)
		return (NULL);
	new_mem = set_worddup(s, c, new_mem);
	return (new_mem);
}
