/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:32:16 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/25 13:46:29 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_first(int infd, int pfd[2], const char *cmd, char **envp)
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
}

static void	child_last(int in, int outfd, const char *cmd, char **envp)
{
	if (in >= 0)
		dup2(in, STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	if (in >= 0)
		close(in);
	close(outfd);
	exec_one(cmd, envp);
}

static int	wait_last_two(pid_t p1, pid_t p2)
{
	int	status;
	int	code;

	code = 0;
	if (waitpid(p1, NULL, 0) < 0)
		code = 1;
	if (waitpid(p2, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			code = 128 + WTERMSIG(status);
	}
	return (code);
}

int	run_pipeline(t_px *px, int first_fd, int cmd_start, int cmd_end)
{
	int		pfd[2];
	pid_t	p1;
	pid_t	p2;

	(void)cmd_end;
	if (pipe(pfd) < 0)
		return (-1);
	p1 = fork();
	if (p1 == 0)
		child_first(first_fd, pfd, px->av[cmd_start], px->envp);
	p2 = fork();
	if (p2 == 0)
	{
		if (first_fd >= 0)
			close(first_fd);
		close(pfd[WR]);
		child_last(pfd[RD], px->out_fd, px->av[cmd_start + 1], px->envp);
	}
	if (first_fd >= 0)
		close(first_fd);
	close(pfd[RD]);
	close(pfd[WR]);
	close(px->out_fd);
	return (wait_last_two(p1, p2));
}
