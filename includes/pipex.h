#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include "../libft/libft.h"

# define ERR_INPUT "Invalid arguments\nUsage: ./pipex file1 cmd1 cmd2 file2"
# define ERR_PIPE "Pipe error"
# define ERR_FORK "Fork error"
# define ERR_FILE "File error"
# define ERR_CMD "Command not found"
# define ERR_EXECVE "Execve error"

typedef struct s_pipex
{
    int     in_fd;
    int     out_fd;
    int     pipe_fd[2];
    pid_t   pid1;
    pid_t   pid2;
    char    **paths;
    char    **cmd_args;
    char    *cmd_path;
}   t_pipex;

// Main functions
void    pipex(t_pipex *data, char **argv, char **envp);
void    execute_cmd(t_pipex *data, char *cmd, char **envp);

// Utils
char    **get_paths(char **envp);
char    *get_cmd_path(char **paths, char *cmd);
void    free_array(char **arr);

// Error handling
void    error_exit(char *msg, int exit_code);
void    close_fds(t_pipex *data);

#endif