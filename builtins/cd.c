//cd.c

#include "../minishell.h"

int	change_dir(char *path, t_env_info *env)
{
	// chdir시 path가 유효하지 않을 경우 처리하는 함수
	// if chdir fails, print out error message referring errono
	int 	ret;
	char	buf[4096];

	ret = chdir(path);
	if (ret == 0)
	{
		ft_setenv(env, "OLDPWD", ft_getenv(env, "PWD"));
		getcwd(buf, 400);
		ft_setenv(env, "PWD", ft_strdup(buf));
	}
	else if (ret == -1) 
		perror("cd");
	return (ret);
}

int	mini_cd(t_cmd_info *cmd, t_env_info *env)
{
	char	*path;
	char	*oldpwd;
	char	buf[4096];

	if (cmd_and_av_cnt(cmd->cmd_and_av) > 2) 	//argument가 2개 이상인 경우
		return(printstderr("cd: too many arguments\n"));
	else if (cmd_and_av_cnt(cmd->cmd_and_av) == 1) // arguments 없는 경우
	{
		path = ft_getenv(env, "HOME"); 
		if (!path)  //HOME 환경변수가 없는 경우 unset으로 env HOME없애고 test해볼것
			return(printstderr("cd: HOME not set\n"));
		return (change_dir(path, env)); // chdir시 path가 유효하지 않을 경우 처리하는 함수 필요
	}
	else // argument 1인 경우
	{
		path = cmd->cmd_and_av[1]; 	// argument 한개인 경우 해당 path로
		if (!ft_strncmp(path, "-", ft_strlen(path)))
		{
			path = ft_getenv(env, "OLDPWD");
			if (!path)
				return(printstderr("cd: OLDPWD not set"));
			printf("%s\n", path); // oldpwd 절대경로 print
		}
		else if (!ft_strncmp(path, "~", ft_strlen(path)))
		{
			path = ft_getenv(env, "HOME");
			if (!path)
				return(printstderr("cd: HOME not set\n"));
		}
		else
		{	
			//input path 첫 char가 '/'이면 절대경로이므로 chage_dir에 그대로 전달 
			//아니면 현재 cwd + / + input path append하여 path
			if (*path != '/')
			{
				getcwd(buf, 400);
				path = ft_strjoin(ft_strjoin(buf, "/"), path);
			}
		}
		return (change_dir(path, env));
	}
}
