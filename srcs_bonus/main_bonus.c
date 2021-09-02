/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:13:35 by alabalet          #+#    #+#             */
/*   Updated: 2021/09/02 18:52:07 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

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
