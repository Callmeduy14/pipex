#include "pipex.h"

static int	open_infile(t_px *px)
{
	if (px->here_doc)
		return (px_build_heredoc(px->limiter));
	return (open(px->av[1], O_RDONLY));
}

static int	open_outfile(t_px *px)
{
	if (px->here_doc)
		return (open(px->av[px->ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (open(px->av[px->ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644));
}

static int	parse_args(t_px *px, int ac, char **av, char **envp)
{
	px->ac = ac;
	px->av = av;
	px->envp = envp;
	px->here_doc = 0;
	px->limiter = NULL;
	if (ac < 5)
		return (err_msg("usage: ./pipex file1 cmd1 cmd2 file2", 1), 0);
	if (str_equal(av[1], "here_doc"))
	{
		if (ac < 6)
			return (err_msg("usage: ./pipex here_doc LIMITER cmd cmd1 file", 1), 0);
		px->here_doc = 1;
		px->limiter = av[2];
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_px	px;
	int	infd;
	int	first_cmd;
	int	last_cmd;
	int	code;

	if (!parse_args(&px, ac, av, envp))
		return (1);
	infd = open_infile(&px);
	px.out_fd = open_outfile(&px);
	if (infd < 0)
		err_file(px.here_doc ? "here_doc" : av[1]);
	if (px.out_fd < 0)
		return (err_file(av[ac - 1]), 1);
	first_cmd = px.here_doc ? 3 : 2;
	last_cmd = ac - 2;
	code = run_pipeline(&px, infd, first_cmd, last_cmd);
    if (code < 0)
        return (1);
    return (code);
}
