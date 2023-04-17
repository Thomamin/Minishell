/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systemcall2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:59:37 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/12 15:35:21 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_write(int fd, const void *buf, size_t byte)
{
	int	ret;

	ret = write(fd, buf, byte);
	if (ret == -1)
		exit_errno("write()", strerror(errno), EXIT_FAILURE);
	return (ret);
}

void	*ft_malloc(size_t size, size_t n)
{
	void	*ret;

	ret = malloc(size * n);
	if (ret == NULL)
	{
		exit_errno("malloc()", strerror(errno), EXIT_FAILURE);
	}
	return (ret);
}

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
