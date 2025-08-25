/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:30:15 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/25 12:16:59 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	line_equals_limiter(const char *line, const char *lim)
{
	size_t	len_line;
	size_t	len_lim;

	if (!line || !lim)
		return (0);
	len_line = ft_strlen(line);
	if (len_line > 0 && line[len_line - 1] == '\n')
		len_line--;
	len_lim = ft_strlen(lim);
	if (len_line != len_lim)
		return (0);
	return (ft_strncmp(line, lim, len_line) == 0);
}

static int	heredoc_write_line(int fd, const char *line)
{
	ssize_t	n;
	size_t	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	n = write(fd, line, (int)len);
	if (n < 0)
		return (0);
	return (1);
}

static void	heredoc_loop(int out_fd, const char *limiter)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (line_equals_limiter(line, limiter))
		{
			free(line);
			break ;
		}
		if (!heredoc_write_line(out_fd, line))
		{
			free(line);
			break ;
		}
		free(line);
		line = get_next_line(0);
	}
}

int	px_build_heredoc(const char *limiter)
{
	int	pfd[2];

	if (pipe(pfd) < 0)
		return (-1);
	heredoc_loop(pfd[1], limiter);
	close(pfd[1]);
	return (pfd[0]);
}
