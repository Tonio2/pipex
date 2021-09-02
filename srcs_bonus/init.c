/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 18:51:45 by alabalet          #+#    #+#             */
/*   Updated: 2021/09/02 19:46:39 by alabalet         ###   ########.fr       */
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

void	init_tmpfile(t_vars *v, char **av)
{
	char	*line;
	char	*delim;
	int		cpt;

	v->fd[0] = open("f/.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (v->fd[0] == -1)
		ft_error(strerror(errno), 0);
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
		free(line);
		line = get_next_line(0);
	}
	free(line);
	free(delim);
	close(v->fd[0]);
}

void	init_vars2(t_vars *v, int ac, char **av, char **e)
{
	int	cpt;

	v->n = ac - 4;
	if (!ft_strlen(av[v->n + 1]) || !ft_strlen(av[v->n + 2]))
		ft_error("Usage: ./pipex here_doc DELIMITER cmd1 ... cmdn outfile\n", 0);
	v->pipefd = malloc((v->n - 1) * sizeof(int *));
	cpt = -1;
	while (++cpt < v->n - 1)
	{
		v->pipefd[cpt] = malloc(2 * sizeof(int));
		pipe(v->pipefd[cpt]);
	}
	init_tmpfile(v, av);
	v->fd[0] = open("f/.tmp", O_RDONLY);
	if (v->fd[0] == -1)
		ft_error(strerror(errno), 0);
	v->fd[1] = open(av[v->n + 3], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (v->fd[1] == -1)
		ft_error(av[v->n + 3], 2);
	v->param = malloc(v->n * sizeof(t_param));
	init_params(v->n, v->param, av + 1, e);
}
