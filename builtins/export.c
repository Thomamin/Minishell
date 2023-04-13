//export.c

#include "../minishell.h"

int	mini_export(t_cmd_info *cmd, t_info_env *env)
{
	int	i;

	if (cmd_and_av_cnt(cmd->cmd_and_av) == 1) //argument 없을 경우 환경변수들을 alphabet order 출력
	{
		;
		
	}
	i = 1;
	while (cmd->cmd_and_av[i])
	{
	// 각 argument들 'identifier=value'형태인지 검사 아닌 경우 'argument값: not a valid identifier' error stderr출력
	//idendifier는 alphabet이나 ‘_’ 가능. 실패시 error code를  exit_status에 반영
	

	// '='기준으로 identifier와 value로 분류
	
	// t_info_env 구조체 생성
	// key(identifier)와 value값 assign
	// env list에 add

		i++;
	}


	return (0);
}
