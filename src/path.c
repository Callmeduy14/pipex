/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:31:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/12 20:55:40 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	starts_with(const char *s, const char *pfx)
{
	int	i;

	if (!s || !pfx)
		return (0);
	i = 0;
	while (pfx[i])
	{
		if (s[i] != pfx[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_absolute_or_rel(const char *s)
{
	if (!s || !*s)
		return (0);
	if (s[0] == '/' || starts_with(s, "./") || starts_with(s, "../"))
		return (1);
	if (ft_strchr(s, '/'))
		return (1);
	return (0);
}

char	**px_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp && envp[i] && !starts_with(envp[i], "PATH="))
		i++;
	if (!envp || !envp[i])
		return (ft_split("/usr/local/bin:/usr/bin:/bin", ':'));
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*px_join_path(char **paths, const char *cmd)
{
	int		i;
	char	*tmp;
	char	*full;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full)
			return (NULL);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}
