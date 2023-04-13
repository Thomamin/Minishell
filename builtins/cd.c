//cd.c

#include "../minishell.h"

int	change_dir(char *path, t_env_info *env)
{
	// chdir시 path가 유효하지 않을 경우 처리하는 함수
	// if chdir fails, print out error message referring errono
	int ret;

	ret = chdir(path);
	if (ret == 0)
	{
		ft_setenv(env, "OLDPWD", ft_getenv(env, "PWD"));
		ft_setenv(env, "PWD", path);
	}
	else if (ret == -1) 
		perror("cd");
	return (ret);
}

int	mini_cd(t_cmd_info *cmd, t_env_info *env)
{
	char	*path;
	char	*oldpwd;

	if (cmd_and_av_cnt(cmd->cmd_and_av) > 2) 	//argument가 2개 이상인 경우
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
		return (change_dir(path, env)); // chdir시 path가 유효하지 않을 경우 처리하는 함수 필요
	}
	path = cmd->cmd_and_av[1]; 	// argument 한개인 경우 해당 path로
	if (!ft_strncmp(path, "-", ft_strlen(path))) //cd에만 해당하는 metacharacter이므로 cd에서 처리
	{
		path = ft_getenv(env, "OLDPWD");
		if (!path)
		{
			printstderr("cd: OLDPWD not set");
			return (1);
		}
		printf("%s\n", path); // oldpwd 절대경로 print
	}
	else if (!ft_strncmp(path, "~", ft_strlen(path))) //cd에만 해당하는 metacharacter이므로 cd에서 처리
	{
		path = ft_getenv(env, "HOME");
		if (!path)
		{
			printstderr("cd: HOME not set");
			return (1);
		}
	}
	else
	{	
		path = ft_strjoin("/", path);
		path = ft_strjoin(ft_getenv(env, "PWD"), path);
	}
	return (change_dir(path, env));
}
