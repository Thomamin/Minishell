//cd.c

#include "../minishell.h"

int	change_dir(char *path)
{
	// chdir시 path가 유효하지 않을 경우 처리하는 함수
	// if chdir fails, print out error message referring errono
	if (chdir(path) == -1) 
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

int	mini_cd(t_cmd_info *cmd, t_env_info *env)
{
	char	*path;
	char	*oldpwd;

	if (cmd_and_av_cnt(cmd->cmd_and_av) > 3) 	//argument가 2개 이상인 경우
	{
		printstderr("cd: too many arguments\n");
		return (1);
	}
	else if (cmd_and_av_cnt(cmd->cmd_and_av) == 1) // arguments 없는 경우
	{
		path = ft_getenv(env, "HOME"); 
		if (!path)  //HOME 환경변수가 없는 경우 unset으로 env HOME없애고 test해볼것
		{
			printstderr("HOME not set\n");
			return (1);
		}
		return (change_dir(path)); // chdir시 path가 유효하지 않을 경우 처리하는 함수 필요
	}
	path = cmd->cmd_and_av[1]; 	// argument 한개인 경우 해당 path로
	if (ft_strncmp(path, "-", ft_strlen(path))) //cd에만 해당하는 metacharacter이므로 cd에서 처리
	{
		oldpwd = ft_getenv(env, "OLDPWD");
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
