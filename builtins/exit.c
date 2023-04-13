// exit.c 

#include "../minishell.h"

int mini_exit(t_cmd_info *cmd)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (cmd_and_av_cnt(cmd->cmd_and_av) > 2)
	{
		printstderr("exit: too many arguments\n");
		return (1);
	}
	if (cmd_and_av_cnt(cmd->cmd_and_av) == 2)
	{
		while (*(cmd->cmd_and_av[1] + i))
		{
			if (!ft_isdigit(*(cmd->cmd_and_av[1] + i)))
			{
				printstderr("exit: %s: numeric argument required");
				return (1);
			}
			i++;
		}
		ret = ft_atoi(cmd->cmd_and_av[1]);
	}	

	//minishell program exit이 exit() 함수 호출로 exit status code요건을 맞출 수 없을 경우
		//exit을 호출한 main process를 종료하도록
		//int argument가 있으면 int로 변환하여 return -> exit_status에 return값 update
		//return (ret);

	exit(ret);
}
