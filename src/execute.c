#include "pipex.h"

void    child_process(t_pipex *data, char *cmd, char **envp)
{
    dup2(data->in_fd, STDIN_FILENO);
    dup2(data->pipe_fd[1], STDOUT_FILENO);
    close_fds(data);
    execute_cmd(data, cmd, envp);
}

void    parent_process(t_pipex *data, char *cmd, char **envp)
{
    dup2(data->pipe_fd[0], STDIN_FILENO);
    dup2(data->out_fd, STDOUT_FILENO);
    close_fds(data);
    execute_cmd(data, cmd, envp);
}

void    pipex(t_pipex *data, char **argv, char **envp)
{
    data->pid1 = fork();
    if (data->pid1 < 0)
        error_exit(ERR_FORK, 1);
    if (data->pid1 == 0)
        child_process(data, argv[2], envp);
    data->pid2 = fork();
    if (data->pid2 < 0)
        error_exit(ERR_FORK, 1);
    if (data->pid2 == 0)
        parent_process(data, argv[3], envp);
    close_fds(data);
    waitpid(data->pid1, NULL, 0);
    waitpid(data->pid2, NULL, 0);
}

void    execute_cmd(t_pipex *data, char *cmd, char **envp)
{
    data->cmd_args = ft_split(cmd, ' ');
    if (!data->cmd_args)
        error_exit("Malloc error", 1);
    data->cmd_path = get_cmd_path(data->paths, data->cmd_args[0]);
    if (!data->cmd_path)
    {
        free_array(data->cmd_args);
        error_exit(ERR_CMD, 127);
    }
    if (execve(data->cmd_path, data->cmd_args, envp) < 0)
    {
        free(data->cmd_path);
        free_array(data->cmd_args);
        error_exit(ERR_EXECVE, 1);
    }
}