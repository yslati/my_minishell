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
#include  <errno.h>
#include  <signal.h>
#include "../libft/libft.h"

# define SIZE		16384
# define APPEND		'a'
# define TRUNC		'>'
# define READ		'<'
# define TRUE		1
# define FLASE		0
# define PIPE		124
# define S_COLON	59
# define STX_ERR	1
# define RDIN_ERR	2
# define SPLT_ERR	3

# define HELLO "\n\n======> SAFE <======\n\n"

typedef		struct	s_cmd
{
	char			*cmd;
	char			**args;
	char			start;
	char			end;
	char			redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef		struct	s_ms
{
	char			*input;
	char			*output;
	int				err;
	short			is_op;
	t_cmd			*cmds;
	int				cmds_count;
	int				pp_count;
	char			*path;
	char			*old_path;
	char			*ptr;
	char			**tab;
	char			**env;
	int				ret;
}					t_ms;

void				get_input(t_ms *ms);
size_t				ft_strlen(const char *s);
int					tb_len(char **table);
char				**free_str_table(char **tab, int size);
void				init(t_ms *ms, char step);
void				parse(t_ms *ms);
int					char_counter(char *s, char c);
char				**parse_split(char const *s, char c);
void				print_tab(char **tab);
void				print_cmds(t_cmd *cmds);
void				errex(t_ms *ms, int ex);
char				**dup_str_tab(char **arr);
void				new_cmd(t_cmd **head, char del, char **tab);
void				minishell(char **env, int step);

#endif
