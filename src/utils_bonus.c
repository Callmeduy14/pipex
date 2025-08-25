/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:31:43 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/25 10:29:18 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	open_infile(t_px *px)
{
	if (px->here_doc == 1)
		return (px_build_heredoc(px->limiter));
	return (open(px->av[1], O_RDONLY));
}

static int	open_outfile(t_px *px)
{
	int	flags;

	if (px->here_doc)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	return (open(px->av[px->ac - 1], flags, 0644));
}

static int	validate_io(t_px *px, int infd, int ac, char **av)
{
	if (infd < 0)
	{
		if (px->here_doc == 1)
			err_file("here_doc");
		else
			err_file(av[1]);
	}
	if (px->out_fd < 0)
	{
		err_file(av[ac - 1]);
		return (0);
	}
	return (1);
}

int	open_files(t_px *px, int *infd)
{
	*infd = open_infile(px);
	px->out_fd = open_outfile(px);
	if (!validate_io(px, *infd, px->ac, px->av))
		return (0);
	return (1);
}

char	*px_dup_unquoted(const char *s)
{
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len >= 2 && ((s[0] == '\'' && s[len - 1] == '\'')
			|| (s[0] == '"' && s[len - 1] == '"')))
		return (ft_substr(s, 1, len - 2));
	return (ft_strdup(s));
}
