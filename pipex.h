#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>



typedef struct s_param
{
	char	**paths;
	char	**cmd;
}			t_param;

char	**get_cmds(char **e, char *cmd);
void	exec_cmd(int in_stream, int out_stream, t_param param, char **e);
void	ft_free_matrix(t_param *param, int nb_param);
void	ft_error(char *str, int type);
#endif
