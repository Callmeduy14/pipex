/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:32:08 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/25 14:07:50 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_first(int infd, int pfd[2], const char *cmd, char **envp)
{
	int	nullfd;

	if (infd >= 0)
		dup2(infd, STDIN_FILENO);
	else
	{
		nullfd = open("/dev/null", O_RDONLY);
		if (nullfd < 0)
			_exit(1);
		dup2(nullfd, STDIN_FILENO);
		close(nullfd);
	}
	dup2(pfd[WR], STDOUT_FILENO);
	if (infd >= 0)
		close(infd);
	close(pfd[RD]);
	close(pfd[WR]);
	exec_one(cmd, envp);
	_exit(127);
}

void	child_mid(int in, int out, const char *cmd, char **envp)
{
	if (in >= 0)
		dup2(in, STDIN_FILENO);
	if (out >= 0)
		dup2(out, STDOUT_FILENO);
	if (in >= 0)
		close(in);
	if (out >= 0)
		close(out);
	exec_one(cmd, envp);
	perror("execve");
	_exit(127);
}

static void	xdup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
	{
		perror("dup2");
		_exit(1);
	}
}

void	child_last(int in, int outfd, const char *cmd, char **envp)
{
	int	nullfd;

	if (in >= 0)
		xdup2(in, STDIN_FILENO);
	else
	{
		nullfd = open("/dev/null", O_RDONLY);
		if (nullfd < 0)
		{
			perror("open /dev/null");
			_exit(1);
		}
		xdup2(nullfd, STDIN_FILENO);
		close(nullfd);
	}
	xdup2(outfd, STDOUT_FILENO);
	if (in >= 0)
		close(in);
	close(outfd);
	exec_one(cmd, envp);
	perror("execve");
	_exit(127);
}

int	wait_last(pid_t *pids, int n)
{
	int	i;
	int	status;
	int	code;

	i = 0;
	code = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &status, 0) > 0)
		{
			if (i == n - 1)
			{
				if (WIFEXITED(status))
					code = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					code = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
	return (code);
}
