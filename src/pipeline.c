#include "pipex.h"

static void	child_first(int infd, int pfd[2], const char *cmd, char **envp)
{
	if (infd >= 0)
		dup2(infd, STDIN_FILENO);
	else
		dup2(open("/dev/null", O_RDONLY), STDIN_FILENO);
	dup2(pfd[WR], STDOUT_FILENO);
	close(infd);
	close_pipe(pfd);
	exec_one(cmd, envp);
}

static void	child_mid(int in, int out, const char *cmd, char **envp)
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

static int	wait_last(pid_t *pids, int n)
{
	int		i;
	int		status;
	int		code;

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

int	run_pipeline(t_px *px, int first_fd, int cmd_start, int cmd_end)
{
	int		i;
	int		pfd[2];
	int		in;
	pid_t	*pids;
	int		ncmd;
	int		code;

	ncmd = cmd_end - cmd_start + 1;
	pids = (pid_t *)malloc(sizeof(pid_t) * ncmd);
	if (!pids)
		return (-1);
	in = first_fd;
	i = 0;
	while (i < ncmd)
	{
		if (i < ncmd - 1 && pipe(pfd) < 0)
			return (free(pids), -1);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i == 0)
				child_first(in, pfd, px->av[cmd_start + i], px->envp);
			else if (i == ncmd - 1)
				child_last(in, px->out_fd, px->av[cmd_start + i], px->envp);
			else
				child_mid(in, pfd[WR], px->av[cmd_start + i], px->envp);
		}
		if (i > 0)
			close(in);
		if (i < ncmd - 1)
		{
			close(pfd[WR]);
			in = pfd[RD];
		}
		i++;
	}
	code = wait_last(pids, ncmd);
	free(pids);
	return (code);
}
