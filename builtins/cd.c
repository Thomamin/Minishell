/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:27:30 by dmin              #+#    #+#             */
/*   Updated: 2023/04/08 12:27:34 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../minishell.h"

int	cmd_and_av_cnt(char **cmd_and_av)
{
	int	cnt;

	cnt = 0;
	while (cmd_and_av[cnt])
		cnt++;
	return cnt;
}

void printstderr(char *str)
{
	write(2, str, ft_strlen(str));
}

int	change_dir(char *path)
{
	// chdir시 path가 유효하지 않을 경우 처리하는 함수
	// if chdir fails, print out error message referring errono
	if (chdir(path) == -1) 
	{
		perror(path);
		return (-1);
	}
	return (0);
}

int	mini_cd(t_cmd_info *cmd_info)
{
	char	*path;
	char	*oldpwd;

	if (cmd_and_av_cnt(cmd_info->cmd_and_av) > 3) 	//argument가 2개 이상인 경우
	{
		printstderr("cd: too many arguments\n");
		return (1);
	}
	else if (cmd_and_av_cnt(cmd_info->cmd_and_av) == 1) // arguments 없는 경우
	{
		path = getenv("home"); 
		if (!path)  //HOME 환경변수가 없는 경우 unset으로 env HOME없애고 test해볼것
		{
			printstderr("HOME not set\n");
			return (1);
		}
		return (change_dir(path)); // chdir시 path가 유효하지 않을 경우 처리하는 함수 필요
	}
	path = cmd_info->cmd_and_av[1]; 	// argument 한개인 경우 해당 path로
	if (path == "-") //cd에만 해당하는 metacharacter이므로 cd에서 처리
	{
		oldpwd = getenv("oldpwd");
		if (!oldpwd)
		{
			printstderr("cd: OLDPWD not set");
			return (1);
		}
		printf("%s\n", oldpwd); // oldpwd 절대경로 print
		path = oldpwd;
	}
	return (change_dir(path));
}
