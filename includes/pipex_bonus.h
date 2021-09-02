/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 23:14:44 by alabalet          #+#    #+#             */
/*   Updated: 2021/09/02 19:54:42 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct s_param
{
	char	**paths;
	char	**cmd;
}			t_param;

typedef struct s_vars
{
	t_param	*param;
	int		**pipefd;
	int		fd[2];
	int		n;
}			t_vars;

char	**get_cmds(char **e, char *cmd);
void	exec_cmd(int in_stream, int out_stream, t_param param, char **e);
void	ft_free_matrix(t_param *param, int nb_param);
void	ft_error(char *str, int type);

char	*get_next_line(int fd);
int		parse_buf(char **line, char *buf);
void	ft_strcpy(char *dst, char *src);
int		my_strlen(char *str);
void	my_free(char *str);

void	init_vars2(t_vars *v, int ac, char **av, char **e);
void	init_tmpfile(t_vars *v, char **av);
void	init_vars(t_vars *v, int ac, char **av, char **e);
void	init_params(int n, t_param *param, char **av, char **e);
void	init_fd(int fd[2], int n, char **av);
#endif
