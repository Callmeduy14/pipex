/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:26:47 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/12 19:26:48 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_file(const char *name)
{
	ft_putstr_fd("pipex: ", 2);
	if (name)
		ft_putstr_fd((char *)name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

void	err_cmd(const char *name)
{
	ft_putstr_fd("pipex: ", 2);
	if (name)
		ft_putstr_fd((char *)name, 2);
	ft_putendl_fd(": command not found", 2);
}

void	err_msg(const char *msg, int code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd((char *)msg, 2);
	(void)code;
}

int	exit_status_from_errno(const char *path)
{
	(void)path;
	if (errno == EACCES || errno == EISDIR)
		return (126);
	if (errno == ENOENT || errno == ENOTDIR)
		return (127);
	return (126);
}
