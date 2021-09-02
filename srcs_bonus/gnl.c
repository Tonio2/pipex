/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabalet <alabalet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:14:17 by alabalet          #+#    #+#             */
/*   Updated: 2021/09/02 15:14:40 by alabalet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"

#define BUFFER_SIZE 4096

int	my_strlen(char *str)
{
	int	cpt;

	cpt = 0;
	if (!str)
		return (0);
	while (str[cpt])
		cpt++;
	return (cpt);
}

void	ft_strcpy(char *dst, char *src)
{
	int	cpt;

	cpt = -1;
	while (src[++cpt])
		dst[cpt] = src[cpt];
	dst[cpt] = 0;
}

int	parse_buf(char **line, char *buf)
{
	char	*tmp;
	int		cpt;
	int		cpt2;
	int		parsing_status;

	tmp = malloc(my_strlen(*line) + my_strlen(buf) + 1);
	cpt = -1 + (*line == 0);
	if (*line)
	{
		while ((*line)[++cpt])
			tmp[cpt] = (*line)[cpt];
	}
	cpt2 = -1;
	while (buf[++cpt2] && buf[cpt2] != '\n')
		tmp[cpt + cpt2] = buf[cpt2];
	parsing_status = (buf[cpt2] == '\n');
	tmp[cpt + cpt2] = buf[cpt2];
	tmp[cpt + cpt2 + parsing_status] = 0;
	ft_strcpy(buf, buf + cpt2 + parsing_status);
	if (*line)
		free(*line);
	*line = ft_strdup(tmp);
	free(tmp);
	return (parsing_status);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			parsing_status;
	int			read_status;

	line = 0;
	if (buf[0])
		parsing_status = parse_buf(&line, buf);
	if (parsing_status == 1)
		return (line);
	read_status = read(fd, buf, BUFFER_SIZE);
	buf[read_status] = 0;
	while (read_status > 0)
	{
		parsing_status = parse_buf(&line, buf);
		if (parsing_status == 1)
			return (line);
		read_status = read(fd, buf, BUFFER_SIZE);
		buf[read_status] = 0;
	}
	if (read_status == 0)
		return (line);
	if (line)
		free(line);
	return (0);
}
