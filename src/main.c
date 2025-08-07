#include "pipex.h"

void    init_data(t_pipex *data)
{
    data->in_fd = -1;
    data->out_fd = -1;
    data->pipe_fd[0] = -1;
    data->pipe_fd[1] = -1;
    data->paths = NULL;
    data->cmd_args = NULL;
    data->cmd_path = NULL;
}

int main(int argc, char **argv, char **envp)
{
    t_pipex    data;

    if (argc != 5)
        error_exit(ERR_INPUT, 1);
    init_data(&data);
    data.in_fd = open(argv[1], O_RDONLY);
    if (data.in_fd < 0)
        error_exit(ERR_FILE, 1);
    data.out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (data.out_fd < 0)
        error_exit(ERR_FILE, 1);
    if (pipe(data.pipe_fd) < 0)
        error_exit(ERR_PIPE, 1);
    data.paths = get_paths(envp);
    pipex(&data, argv, envp);
    close_fds(&data);
    free_array(data.paths);
    return (0);
}