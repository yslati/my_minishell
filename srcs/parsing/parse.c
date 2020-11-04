/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:21:10 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/04 11:48:27 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			is_from(char c, char *set)
{
	if (set)
		while (*set)
		{
			if (*set++ == c)
				return (1);
		}
	return (0);
}

void		parse_scolon(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' '))) // need free
		errex(ms, SPLT_ERR);
	free(tmp);
	b = i;
}

void		parse_pipe(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	ms->pp_count++;
	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ')))
		errex(ms, SPLT_ERR);
	free(tmp);
}

void		parse_trunc_rdr(t_ms *ms, int b, int *i, char *s)
{
	char *tmp;

	ms->redir = TRUNC;
	if (s[*i + 1] == '>')
		ms->redir = APPEND;
	tmp = ft_strldup(s + b, *i - b);
	if (!(ms->tab = parse_split(tmp, ' ')))
		errex(ms, SPLT_ERR);
	free(tmp);
	*i += (s[*i + 1] == '>');
}

void		parse_read_rdr(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	ms->redir = READ;
	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ')))
		errex(ms, SPLT_ERR);
	free(tmp);
}

void		parse_scolon_pp(t_ms *ms, int b, int *i, char *s)
{
	ms->cmds_count++;
	if (s[*i] == S_COLON)
		parse_scolon(ms, b, *i, ms->input);
	else if (s[*i] == PIPE)
		parse_pipe(ms, b, *i, ms->input);
	else if (s[*i] == TRUNC)
		parse_trunc_rdr(ms, b, i, ms->input);
	else if (s[*i] == READ)
		parse_read_rdr(ms, b, *i, ms->input);
	new_cmd(ms, s[*i], ms->tab);
	ms->tab = NULL;
	ms->redir = 0;
}

void		parse(t_ms *ms)
{
	int		i;
	int		b;
	char	*s;

	if ((i = read(0, ms->input, SIZE)) < 0)
	{
		ms->err = RDIN_ERR;
		errex(ms, 0);
	}
	ms->input[i - 1] = 0;
	s = ms->input;
	i = -1;
	b = 0;
	
	while (ms->input[++i])
		if (is_from(ms->input[i], "|;><"))	
		{
			parse_scolon_pp(ms, b, &i, ms->input);
			b = i + 1;
		}
	ms->tab = parse_split(ms->input + b, ' ');
	new_cmd(ms, S_COLON, ms->tab);
	++ms->cmds_count;
	ms->tab = NULL;
	ms->cmds = get_head(ms->cmds);
	print_cmds(ms->cmds);
}
