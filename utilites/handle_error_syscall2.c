/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_syscall2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonjo <hyeonjo@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:55:34 by hyeonjo           #+#    #+#             */
/*   Updated: 2023/04/27 12:55:43 by hyeonjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(char *fname, int oflag, int mode)
{
	int	fd;

	fd = open(fname, oflag, mode);
	if (fd < 0)
		exit_errno(fname, strerror(errno), EXIT_FAILURE);
	return (fd);
}

int	ft_close(int fd)
{
	if (close(fd) == -1)
		exit_errno("close()", strerror(errno), EXIT_FAILURE);
	return (-2);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		exit_errno("dup2()", strerror(errno), EXIT_FAILURE);
}

void	ft_pipe(int *fds)
{
	if (pipe(fds) == -1)
		exit_errno("pipe()", strerror(errno), EXIT_FAILURE);
}

pid_t	ft_fork(void)
{
	int	ret;

	ret = fork();
	if (ret < 0)
		exit_errno("fork()", strerror(errno), EXIT_FAILURE);
	return (ret);
}
