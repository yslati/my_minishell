/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:05:50 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/01 14:37:16 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

# ifndef N_OF_FILES_IN_LINE
#  define N_OF_FILES_IN_LINE 3
# endif

char	*join_del_str(char *str, char *line)
{
	char *tmp;

	tmp = str;
	str = ft_strjoin(str, line);
	free(tmp);
	return (str);
}

int		main(void)
{
	char *files;
	char *line;
	int r;
	int n_lines;
	int fd;
	int fd1;
	int l;

	fd = open("./source_files", O_RDONLY);
	fd1 = open("./Makefile_test", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	n_lines = 1;
	files = ft_strdup("");
	ft_putstr_fd("FILES = ", fd1);
	r = 1;
	while (r > 0)
	{
		r = get_next_line(fd, &line);
		if (!r)
		{
			free(line);
			break ;
		}
		l = ft_strlen(line);
		if (l)
			line[l - 1] = ' ';
		if (n_lines == N_OF_FILES_IN_LINE)
			n_lines = 1;
		else
			n_lines++;
		if (n_lines == N_OF_FILES_IN_LINE)
		{
			files = join_del_str(files, line);
			files = join_del_str(files, "\\");
			ft_putendl_fd(files, fd1);
			free(files);
			files = ft_strdup("\t\t");
		}
		else
			files = join_del_str(files, line);
		free(line);
	}
	free(files);
	close(fd);
	close(fd1);
}