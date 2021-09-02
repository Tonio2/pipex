/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:02:54 by alabalet          #+#    #+#             */
/*   Updated: 2021/09/02 18:42:59 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		execve(param.paths[cpt], param.cmd, e);
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
