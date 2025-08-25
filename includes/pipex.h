/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:27:50 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/14 20:45:06 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

# define X_OK_FLAG 1
# define RD 0
# define WR 1

typedef struct s_px
{
	int		here_doc;
	char	*limiter;
	int		in_fd;
	int		out_fd;
	int		ac;
	char	**av;
	char	**envp;
}	t_px;

void		err_file(const char *name);
void		err_cmd(const char *name);
void		err_msg(const char *msg, int code);
int			exit_status_from_errno(const char *path);

char		**px_paths(char **envp);
char		*px_join_path(char **paths, const char *cmd);
int			is_absolute_or_rel(const char *s);

char		**ft_split_quotes(const char *s);

int			sq_isspace(char c);
int			sq_in_quote_next(int st, char c);
int			sq_handle_backslash_scan(const char **pp);

const char	*sq_skip_spaces(const char *p);
void		sq_skip_one_token(const char **pp);
int			sq_token_span(const char *s);
int			sq_unquote_copy(char *dst, const char *src, int n);
void		sq_free_tab(char **tab, int n);

void		free_array(char **a);
int			str_equal(const char *a, const char *b);
int			starts_with(const char *s, const char *pfx);
void		close_fd(int *fd);
void		close_pipe(int pfd[2]);

int			px_build_heredoc(const char *limiter);

void		exec_one(const char *cmd, char **envp);

int			run_pipeline(t_px *px, int first_fd, int cmd_start, int cmd_end);

#endif
