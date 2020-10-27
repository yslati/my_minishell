/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:24:51 by obouykou          #+#    #+#             */
/*   Updated: 2020/06/08 13:24:51 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
#include  <dirent.h>
#include "../libft/libft.h"

# define SIZE 4194304
# define APPEND	1
# define TRUNC	2
# define READ	3

# define HELLO "\n======> SAFE <======"

typedef		struct	s_cmd
{
	char			*cmds;
	char			**args;
	char			start;
	char			end;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef		struct	s_ms
{
	char			input[SIZE];
	char			output[SIZE];
	short			is_op;
	t_cmd			cmd;
	int				pp_count;
	char			*path;
	char			*old_path;
	char			*ptr;
	char			**tab;
	int				ret;
}					t_ms;

void				get_input(t_ms *ms);
size_t				ft_strlen(const char *s);
int					tb_len(char **table);
char				**free_str_table(char **tab, int size);
void				ft_exit(t_ms *ms);
void				ft_echo(t_ms *ms);
void				ft_cmd(t_ms *ms);
void				init(t_ms *ms);
void				print_tab(char **tab);


#endif
