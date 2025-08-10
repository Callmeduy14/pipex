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
	if (!path)
		return (127);
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		return (126);
	return (127);
}
