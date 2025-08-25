/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:31:36 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/12 19:31:37 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*resolve_cmd_path(char **args, char **envp)
{
	char	**paths;
	char	*path;

	if (!args || !args[0])
		return (NULL);
	if (is_absolute_or_rel(args[0]))
	{
		if (access(args[0], F_OK) == 0)
			return (ft_strdup(args[0]));
		return (NULL);
	}
	paths = px_paths(envp);
	if (!paths)
		return (NULL);
	path = px_join_path(paths, args[0]);
	free_array(paths);
	return (path);
}

static void	execve_or_exit(char *path, char **args, char **envp)
{
	if (!path)
	{
		if (args && args[0])
			err_cmd(args[0]);
		else
			err_cmd(NULL);
		exit(127);
	}
	execve(path, args, envp);
	exit(exit_status_from_errno(path));
}

void	exec_one(const char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split_quotes(cmd);
	if (!args || !args[0] || !args[0][0])
	{
		free_array(args);
		err_cmd(NULL);
		exit(127);
	}
	path = resolve_cmd_path(args, envp);
	execve_or_exit(path, args, envp);
}
