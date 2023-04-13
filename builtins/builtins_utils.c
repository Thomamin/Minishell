//builtins_utils.c
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

int	ft_is_valid_identifier(char *identifier)
{
//validate variable identifier - 첫글자는 alphabet or _  두번째 이후 char는 alphanumeric or _
	int	i;

	if(!ft_isalpha(*identifier) && *identifier != '_')
		return (0);
	i = 1;
	while (*identifier && (ft_isalnum(*(identifier + i)) || *(identifier + i) == '_'))
	{
		i++;
	}
	if (*identifier)
		return (0);
	return (1);
}