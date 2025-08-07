#include "pipex.h"

char    **get_paths(char **envp)
{
    char    **paths;
    int     i;

    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    return (paths);
}

char    *get_cmd_path(char **paths, char *cmd)
{
    char    *tmp;
    char    *full_path;
    int     i;

    if (access(cmd, X_OK) == 0)
        return (ft_strdup(cmd));
    i = 0;
    while (paths && paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

void    free_array(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}