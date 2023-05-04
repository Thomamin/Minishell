/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmin <dmin@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:25:32 by dmin              #+#    #+#             */
/*   Updated: 2023/04/27 12:48:38 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_tmp_file_num(void)
{
	unsigned int	seed;
	int				urandom_fd;
	ssize_t			bytes_read;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
	{
		perror("Error opening /dev/urandom");
		exit(1);
	}
	bytes_read = read(urandom_fd, &seed, sizeof(seed));
	if (bytes_read < (ssize_t) sizeof(seed))
	{
		perror("Error reading from /dev/urandom");
		exit(1);
	}
	close(urandom_fd);
	return (seed);
}

char	*get_tmp_file_name(void)
{
	int		tmp_num;
	char	*str_num;
	char	*file_name;

	while (1)
	{
		tmp_num = get_tmp_file_num();
		str_num = ft_itoa(tmp_num);
		file_name = ft_strjoin("/tmp/tmp_file_", str_num);
		if (is_exist_file(file_name) == 0)
		{
			free(str_num);
			return (file_name);
		}
		free(file_name);
		free(str_num);
	}
}

void	delete_tmp_file(char *file_name)
{
	if (is_exist_file(file_name))
		unlink(file_name);
	file_name = NULL;
	return ;
}
