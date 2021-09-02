/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:13:35 by alabalet          #+#    #+#             */
/*   Updated: 2021/09/02 18:43:54 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

void	init_fd(int fd[2], int n, char **av)
{
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_error(av[1], 2);
	fd[1] = open(av[n + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
		ft_error(av[n + 2], 2);
}

void	init_params(int n, t_param *param, char **av, char **e)
{
	int	cpt;

	cpt = -1;
	while (++cpt < n)
	{
		param[cpt].cmd = ft_split(av[cpt + 2], ' ');
		param[cpt].paths = get_cmds(e, param[cpt].cmd[0]);
	}
}

void	init_vars(t_vars *v, int ac, char **av, char **e)
{
	int	cpt;

	v->n = ac - 3;
	cpt = 1;
	while (++cpt < v->n + 2)
		if (!ft_strlen(av[cpt]))
			ft_error("Usage: ./pipex infile cmd1 cmd2 [... cmd_n] outfile\n", 0);
	v->pipefd = malloc((v->n - 1) * sizeof(int *));
	cpt = -1;
	while (++cpt < v->n - 1)
	{
		v->pipefd[cpt] = malloc(2 * sizeof(int));
		pipe(v->pipefd[cpt]);
	}
	init_fd(v->fd, v->n, av);
	v->param = malloc(v->n * sizeof(t_param));
	init_params(v->n, v->param, av, e);
}

void	init_vars2(t_vars *v, char **av, char **e)
{
	char	*line;
	char	*delim;
	int		cpt;

	v->fd[0] = open("f/.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (v->fd[0] == -1)
		ft_error(strerror(errno), 0);
	v->fd[1] = open(av[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (v->fd[1] == -1)
		ft_error(av[5], 2);
	delim = malloc(ft_strlen(av[2]) + 2);
	cpt = -1;
	while (av[2][++cpt])
		delim[cpt] = av[2][cpt];
	delim[cpt++] = '\n';
	delim[cpt] = 0;
	line = get_next_line(0);
	while (ft_strncmp(line, delim, ft_strlen(delim)))
	{
		write(v->fd[0], line, ft_strlen(line));
		line = get_next_line(0);
	}
	free(delim);
	close(v->fd[0]);
	v->fd[0] = open("f/.tmp", O_RDONLY);
	if (v->fd[0] == -1)
		ft_error(strerror(errno), 0);
	v->param = malloc(2 * sizeof(t_param));
	init_params(2, v->param, av + 1, e);
	v->n = 2;
	v->pipefd = malloc(sizeof(int *));
	v->pipefd[0] = malloc(2 * sizeof(int));
	pipe(v->pipefd[0]);
}

void	exec_cmds(t_vars v, char **e)
{
	int	cpt;

	if (!fork())
	{
		close(v.pipefd[0][0]);
		exec_cmd(v.fd[0], v.pipefd[0][1], v.param[0], e);
	}
	close(v.pipefd[0][1]);
	waitpid(-1, 0, 0);
	cpt = 0;
	while (++cpt < v.n - 1)
	{
		if (!fork())
		{
			close(v.pipefd[cpt][0]);
			exec_cmd(v.pipefd[cpt - 1][0], v.pipefd[cpt][1], v.param[cpt], e);
		}
		close(v.pipefd[cpt][1]);
		waitpid(-1, 0, 0);
	}
	if (!fork())
		exec_cmd(v.pipefd[v.n - 2][0], v.fd[1], v.param[v.n - 1], e);
	waitpid(-1, 0, 0);
	ft_free_matrix(v.param, 2);
}

int	main(int ac, char **av, char **e)
{
	t_vars	v;

	if (ac > 2 && !ft_strncmp(av[1], "here_doc", 9))
	{
		if (ac != 6)
			ft_error("Usage: ./pipex here_doc DELIMITER cmd1 cmd2 outfile\n", 0);
		init_vars2(&v, av, e);
		exec_cmds(v, e);
		close(v.fd[0]);
		unlink("f/.tmp");
	}
	else
	{
		if (ac < 5)
			ft_error("Usage: ./pipex infile cmd1 cmd2 [... cmd_n] outfile\n", 0);
		init_vars(&v, ac, av, e);
		exec_cmds(v, e);
	}
	return (0);
}
