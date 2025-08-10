#include "pipex.h"

static int	write_line(int fd, const char *buf, int n)
{
	int	w;
	int	t;

	t = 0;
	while (t < n)
	{
		w = write(fd, buf + t, n - t);
		if (w <= 0)
			return (-1);
		t += w;
	}
	return (0);
}

static int	line_equals_limiter(char *line, const char *lim)
{
	size_t	n;

	if (!line)
		return (0);
	n = ft_strlen(line);
	if (n > 0 && line[n - 1] == '\n')
		line[n - 1] = '\0';
	return (str_equal(line, lim));
}

int	px_build_heredoc(const char *limiter)
{
	int		pfd[2];
	char	*line;

	if (pipe(pfd) < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (line_equals_limiter(line, limiter))
		{
			free(line);
			break ;
		}
		write_line(pfd[WR], line, (int)ft_strlen(line));
		free(line);
	}
	close(pfd[WR]);
	return (pfd[RD]);
}
