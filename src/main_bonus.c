/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:52:59 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/25 11:07:25 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	parse_args_bonus(t_px *px, int ac, char **av, char **envp)
{
	px->ac = ac;
	px->av = av;
	px->envp = envp;
	px->here_doc = 0;
	px->limiter = NULL;
	if (ac < 5)
	{
		err_msg("usage: ./pipex file1 cmd1 cmd2 file2", 1);
		return (0);
	}
	if (str_equal(av[1], "here_doc"))
	{
		if (ac < 6)
		{
			err_msg("usage: ./pipex here_doc LIMITER cmd cmd1 file", 1);
			return (0);
		}
		px->here_doc = 1;
		px->limiter = px_dup_unquoted(av[2]);
		if (!px->limiter)
			return (0);
	}
	else
		px->limiter = NULL;
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_px	px;
	int		infd;
	int		first_cmd;
	int		last_cmd;
	int		code;

	if (!parse_args_bonus(&px, ac, av, envp))
		return (1);
	if (!open_files(&px, &infd))
		return (1);
	if (px.here_doc)
		first_cmd = 3;
	else
		first_cmd = 2;
	last_cmd = ac - 2;
	code = run_pipeline(&px, infd, first_cmd, last_cmd);
	if (px.here_doc && px.limiter)
		free(px.limiter);
	if (code < 0)
		return (1);
	return (code);
}
