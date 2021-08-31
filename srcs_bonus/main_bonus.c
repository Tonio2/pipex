/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:13:35 by alabalet          #+#    #+#             */
/*   Updated: 2021/09/01 00:39:53 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	init_params(int fd[2], t_param param[2], char **av, char **e)
{
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
		ft_error(av[1], 2);
	fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
		ft_error(av[4], 2);
	param[0].cmd = ft_split(av[2], ' ');
	param[1].cmd = ft_split(av[3], ' ');
	param[0].paths = get_cmds(e, param[0].cmd[0]);
	param[1].paths = get_cmds(e, param[1].cmd[0]);
}

int	main(int ac, char **av, char **e)
{
	t_param	param[2];
	int		fd[2];
	int		pipefd[2];

	if (ac != 5 || !ft_strlen(av[2]) || !ft_strlen(av[3]))
		ft_error("Usage: ./pipex infile cmd1 cmd2 outfile\n", 0);
	pipe(pipefd);
	init_params(fd, param, av, e);
	if (!fork())
	{
		close(pipefd[0]);
		exec_cmd(fd[0], pipefd[1], param[0], e);
	}
	waitpid(-1, 0, 0);
	if (!fork())
	{
		close(pipefd[1]);
		exec_cmd(pipefd[0], fd[1], param[1], e);
	}
	close(pipefd[1]);
	waitpid(-1, 0, 0);
	ft_free_matrix(param, 2);
	return (0);
}
