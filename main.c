#include "libft.h"
#include "pipex.h"

char	**get_cmds(char **e, char *cmd)
{
	char	**ret;
	int		cpt;
	char	*tmp;

	cpt = -1;
	while (ft_strncmp(e[++cpt], "PATH=", 5))
		;
	ret = ft_split(e[cpt] + 5, ':');
	cpt = -1;
	while (ret[++cpt])
	{
		tmp = ft_strjoin(ret[cpt], "/");
		free(ret[cpt]);
		ret[cpt] = ft_strjoin(tmp, cmd);
		free(tmp);
	}
	return (ret);
}

void	exec_cmd(int in_stream, int out_stream, t_param param, char **e)
{
	int	cpt;

	dup2(in_stream, 0);
	dup2(out_stream, 1);
	close(in_stream);
	close(out_stream);
	cpt = -1;
	while (param.paths[++cpt])
	{
		execve(param.paths[cpt], param.cmd, e);
	}
	ft_error(param.cmd[0], 1);
}

void	ft_free_matrix(t_param *param, int nb_param)
{
	int	cpt;
	int	cpt2;

	cpt = -1;
	while (++cpt < nb_param)
	{
		cpt2 = -1;
		while (param[cpt].paths[++cpt2])
			free(param[cpt].paths[cpt2]);
		free(param[cpt].paths);
		cpt2 = -1;
		while (param[cpt].cmd[++cpt2])
			free(param[cpt].cmd[cpt2]);
		free(param[cpt].cmd);
	}
}

void	ft_error(char *str, int type)
{
	if (!type)
	{
		ft_putstr_fd(str, 2);
	}
	else if (type == 1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **e)
{
	t_param	param[2];
	int		fd[2];
	int		pipefd[2];
	int		child;
	int		status;

	if (ac < 5)
		ft_error("Usage: ./pipex infile cmd1 cmd2 outfile\n", 0);
	if (access(av[1], R_OK) == -1)
		ft_error(av[1], 2);
	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pipe(pipefd);
	param[0].cmd = ft_split(av[2], ' ');
	param[1].cmd = ft_split(av[3], ' ');
	param[0].paths = get_cmds(e, param[0].cmd[0]);
	param[1].paths = get_cmds(e, param[1].cmd[0]);
	child = fork();
	if (!child)
	{
		close(pipefd[0]);
		exec_cmd(fd[0], pipefd[1], param[0], e);
	}
	waitpid(child, 0, 0);
	child = fork();
	if (!child)
	{
		close(pipefd[1]);
		exec_cmd(pipefd[0], fd[1], param[1], e);
	}
	close(pipefd[1]);
	waitpid(child, &status, 0);
	ft_free_matrix(param, 2);
	return (0);
}
