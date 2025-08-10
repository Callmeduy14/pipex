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
}t_px;

/* error.c */
void	err_file(const char *name);
void	err_cmd(const char *name);
void	err_msg(const char *msg, int code);
int		exit_status_from_errno(const char *path);

/* path.c */
char	**px_paths(char **envp);
char	*px_join_path(char **paths, const char *cmd);
int		is_absolute_or_rel(const char *s);

/* split_quotes.c */
char	**ft_split_quotes(const char *s);

/* utils.c */
void	free_array(char **a);
int		str_equal(const char *a, const char *b);
int		starts_with(const char *s, const char *pfx);
void	close_fd(int *fd);
void	close_pipe(int pfd[2]);

/* here_doc.c */
int		px_build_heredoc(const char *limiter);

/* exec.c */
void	exec_one(const char *cmd, char **envp);

/* pipeline.c */
int		run_pipeline(t_px *px, int first_fd, int cmd_start, int cmd_end);

#endif
