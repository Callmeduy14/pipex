/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:27:55 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/25 10:28:46 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"
# include <stdio.h>

typedef struct s_plctx
{
	int		i;
	int		in;
	int		ncmd;
	pid_t	*pids;
	int		pfd[2];
}	t_plctx;

void		child_first(int infd, int pfd[2], const char *cmd, char **envp);
void		child_mid(int in, int out, const char *cmd, char **envp);
void		child_last(int in, int outfd, const char *cmd, char **envp);
int			wait_last(pid_t *pids, int n);

int			pl_open_next_pipe(t_plctx *c);
void		pl_exec_child(t_px *px, t_plctx *c, int cmd_start);
void		pl_parent_postfork(t_plctx *c);
int			pl_run_loop(t_px *px, t_plctx *c, int cmd_start);

int			px_build_heredoc(const char *limiter);
char		*px_dup_unquoted(const char *s);

int			open_files(t_px *px, int *infd);
int			run_pipeline(t_px *px, int first_fd, int cmd_start, int cmd_end);

#endif
