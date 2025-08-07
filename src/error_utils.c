#include "pipex.h"

void    error_exit(char *msg, int exit_code)
{
    ft_putstr_fd("Error: ", 2);
    ft_putendl_fd(msg, 2);
    exit(exit_code);
}

void    close_fds(t_pipex *data)
{
    if (data->in_fd >= 0)
        close(data->in_fd);
    if (data->out_fd >= 0)
        close(data->out_fd);
    if (data->pipe_fd[0] >= 0)
        close(data->pipe_fd[0]);
    if (data->pipe_fd[1] >= 0)
        close(data->pipe_fd[1]);
}