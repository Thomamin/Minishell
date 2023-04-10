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
#include "minishell.h"



int		mini_cd(t_command *cmd)
{
	char	*path;

	if (number of cmd->arguments > 1) 	//argument가 2개 이상인 경우
	{
		printstderr("cd: too many arguments\n");
		return (1);
	}
	else if (number of cmd->arguments) == 0) // arguments 없는 경우
	{
		path = getenv("home"); 
		if (path == NULL)  //HOME 환경변수가 없는 경우 unset으로 env HOME없애고 test해볼것
		{
			printstderr("HOME not set\n");
			return (1);
		}
		return (chdir(path)); // chdir시 path가 유효하지 않을 경우 처리하는 함수 필요
	}
	path = cmd->arguments[0]; 	// argument 한개인 경우 해당 path로
	if (path == "-"인 경우) //cd에만 해당하는 metacharacter이므로 cd에서 처리
	{
		if (oldpwd == NULL)
		{
			printstderr("cd: OLDPWD not set");
			return (1);
		}
		else
		{
			printf("%s\n", oldpwd); // oldpwd 절대경로 print
			return (chdir(oldpwd)); // chdir시 path가 유효하지 않을 경우 처리하는 함수 필요
		}
	}
	else
		return (chdir(path));// chdir시 path가 유효하지 않을 경우 처리하는 함수 필요
	return (0);
}
