
#include "../minishell.h"

int mini_exit(t_cmd_info *cmd)
{
	if (cmd_and_av_cnt(cmd->cmd_and_av) > 2)
	{
		printstderr("exit: too many arguments\n");
		return (1);
	}
	if (!is_number(cmd->cmd_and_av[1]))
	{
		printstderr("exit: %s: numeric argument required");
		return (1);
	}
	
	//minishell program exit
		//exit을 호출한 main process를 종료하도록

	//int argument가 있으면 int로 변환하여 return -> exit_status에 return값 update
}