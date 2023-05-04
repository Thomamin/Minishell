/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:27:11 by dmin              #+#    #+#             */
/*   Updated: 2023/04/26 22:27:31 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join_ascii(char *s1, char s2)
{
	char	*ret;
	size_t	s1_len;

	if (!s1)
	{
		if (!s2)
			return (0);
		ret = (char *)malloc(sizeof(char) * 2);
		ret[0] = s2;
		ret[1] = '\0';
	}
	else
	{
		s1_len = ft_strlen(s1);
		ret = (char *)malloc(sizeof(char) * (s1_len + 2));
		if (!ret)
			return (0);
		ft_strlcpy(ret, s1, s1_len + 1);
		ret[s1_len] = s2;
		ret[s1_len + 1] = '\0';
		free(s1);
	}
	return (ret);
}
