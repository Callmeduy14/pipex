/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_loop_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:27:55 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/25 13:51:05 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	pl_open_next_pipe(t_plctx *c)
{
	if (c->i < c->ncmd - 1)
	{
		if (pipe(c->pfd) < 0)
			return (-1);
	}
	return (0);
}

void	pl_exec_child(t_px *px, t_plctx *c, int cmd_start)
{
	const char	*cmd = px->av[cmd_start + c->i];

	if (c->i == 0)
		child_first(c->in, c->pfd, cmd, px->envp);
	else if (c->i == c->ncmd - 1)
		child_last(c->in, px->out_fd, cmd, px->envp);
	else
		child_mid(c->in, c->pfd[WR], cmd, px->envp);
}

void	pl_parent_postfork(t_plctx *c)
{
	if (c->in >= 0)
		close(c->in);
	if (c->i < c->ncmd - 1)
	{
		close(c->pfd[WR]);
		c->in = c->pfd[RD];
	}
	else
	{
		c->in = -1;
	}
}

int	pl_run_loop(t_px *px, t_plctx *c, int cmd_start)
{
	while (c->i < c->ncmd)
	{
		if (pl_open_next_pipe(c) < 0)
			return (-1);
		c->pids[c->i] = fork();
		if (c->pids[c->i] == 0)
			pl_exec_child(px, c, cmd_start);
		pl_parent_postfork(c);
		c->i++;
	}
	return (0);
}

int	run_pipeline(t_px *px, int first_fd, int cmd_start, int cmd_end)
{
	t_plctx	c;
	int		code;

	c.ncmd = cmd_end - cmd_start + 1;
	c.pids = (pid_t *)malloc(sizeof(pid_t) * c.ncmd);
	if (!c.pids)
		return (-1);
	c.in = first_fd;
	c.i = 0;
	if (pl_run_loop(px, &c, cmd_start) < 0)
	{
		free(c.pids);
		return (-1);
	}
	close(px->out_fd);
	code = wait_last(c.pids, c.ncmd);
	free(c.pids);
	return (code);
}
