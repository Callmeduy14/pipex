/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:31:52 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/25 13:47:10 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	parse_args(t_px *px, int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		err_msg("usage: ./pipex file1 cmd1 cmd2 file2", 1);
		return (0);
	}
	px->ac = ac;
	px->av = av;
	px->envp = envp;
	px->here_doc = 0;
	px->limiter = NULL;
	return (1);
}

static int	open_infile(t_px *px)
{
	return (open(px->av[1], O_RDONLY));
}

static int	open_outfile(t_px *px)
{
	return (open(px->av[px->ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644));
}

int	main(int ac, char **av, char **envp)
{
	t_px	px;
	int		infd;
	int		code;

	if (!parse_args(&px, ac, av, envp))
		return (1);
	infd = open_infile(&px);
	px.out_fd = open_outfile(&px);
	if (infd < 0)
		err_file(av[1]);
	if (px.out_fd < 0)
	{
		err_file(av[ac - 1]);
		if (infd >= 0)
			close(infd);
		return (1);
	}
	code = run_pipeline(&px, infd, 2, 3);
	if (code < 0)
		return (1);
	return (code);
}
