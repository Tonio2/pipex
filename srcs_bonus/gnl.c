#include "pipex_bonus.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 5

int	ft_strlen(char *str)
{
	int	cpt;

	cpt = 0;
	if (!str)
		return (0);
	while (str[cpt]) {
		cpt++;
	}
	return (cpt);
}

char	*ft_strdup(char *str)
{
	char	*ret;
	int		cpt;

	ret = malloc(ft_strlen(str) + 1);
	cpt = -1;
	while (str[++cpt]) {
		ret[cpt] = str[cpt];
	}
	ret[cpt] = 0;
	return (ret);
}

void ft_strcpy(char *dst, char *src) {
	int	cpt;

	cpt = -1;
	while (src[++cpt]) {
		dst[cpt] = src[cpt];
	}
	dst[cpt] = 0;
}

int parse_buf(char **line, char *buf) {
	char	*tmp;
	int		cpt;
	int		cpt2;
	int		parsing_status;

	tmp = malloc(ft_strlen(*line) + ft_strlen(buf) + 1);
	printf("%d\n", ft_strlen(*line) + ft_strlen(buf) + 1);
	if (*line)
		printf("%s\n", *line);
	printf("%s\n", buf);
	cpt = 0;
	if (*line)
	{
		printf("coucou\n");
		while (*line[cpt])
		{
			tmp[cpt] = *line[cpt];
			cpt++;
		}
	}
	cpt2 = 0;
	while (buf[cpt2] && buf[cpt2] != '\n')
	{
		tmp[cpt + cpt2] = buf[cpt2];
		cpt2++;
	}
	parsing_status = (buf[cpt2] == '\n');
	if (parsing_status == 1)
	{
		tmp[cpt + cpt2] = '\n';
		tmp[cpt + cpt2 + 1] = 0;
	}
	else
		tmp[cpt + cpt2] = 0;
	ft_strcpy(buf, buf + cpt2 + parsing_status);
	if (*line)
		free(*line);
	*line = ft_strdup(tmp);
	free(tmp);
	return (parsing_status);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*line;
	int			parsing_status;
	int			read_status;

	line = 0;
	if (buf[0])
		parsing_status = parse_buf(&line, buf);
	if (parsing_status == 1)
		return (line);
	read_status = read(fd, buf, BUFFER_SIZE);
	while (read_status > 0)
	{
		parsing_status = parse_buf(&line, buf);
		if (parsing_status == 1)
			return (line);
		read_status = read(fd, buf, BUFFER_SIZE);
	}
	if (read_status == 0)
		return (line);
	if (line)
		free(line);
	return (0);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("f/infile", O_RDONLY);
	line = get_next_line(fd);
	while (line) {
		printf("%s", line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
