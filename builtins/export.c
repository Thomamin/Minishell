/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:28:06 by dmin              #+#    #+#             */
/*   Updated: 2023/04/08 12:28:08 by dmin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_export(t_cmd_info *cmd, t_info_env *env)
{
	//idendifier는 alphabet이나 ‘_’ 가능. 실패시 error code를  exit_status에 반영
	
	
	if (cmd_and_av_cnt(cmd->cmd_and_av) == 1)
	{
		;
		//argument 없을 경우 환경변수들을 alphabet order 출력
	}
	return (0);
}
