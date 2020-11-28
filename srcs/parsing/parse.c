/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:21:10 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/24 14:20:24 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		parse_scolon(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
}

void		parse_pipe(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
	ms->pp_count++;
}

void		parse_trunc_rdr(t_ms *ms, int b, int *i, char *s)
{
	char *tmp;

	ms->redir = TRUNC;
	if (s[*i + 1] == '>')
		ms->redir = APPEND;
	tmp = ft_strldup(s + b, *i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
	*i += (s[*i + 1] == '>');
}

void		parse_read_rdr(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	ms->redir = READ;
	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
}

int		make_cmd(t_ms *ms, int b, int *i, char *s)
{
	if (s[*i] == S_COLON)
		parse_scolon(ms, b, *i, ms->input);
	else if (s[*i] == PIPE)
		parse_pipe(ms, b, *i, ms->input);
	else if (s[*i] == TRUNC)
		parse_trunc_rdr(ms, b, i, ms->input);
	else if (s[*i] == READ)
		parse_read_rdr(ms, b, *i, ms->input);
	
	if (ms->tab[0])
	{
		ms->cmd_err = ms->tab[0][0] == '\0';
		new_cmd(ms, s[*i], ms->tab);
	}
	free_str_table(ms->tab, tb_len(ms->tab));
	ms->tab = NULL;
	ms->redir = 0;
	ms->cmd_err = 0;
	return (*i + 1);
}

t_cmd		*get_head(t_cmd *cmds, char *err)
{
	if (cmds && cmds->is_err)
		*err = cmds->is_err;
	while (cmds && cmds->prev)
	{
		if (cmds->is_err)
			*err = cmds->is_err;
		cmds = cmds->prev;
	}
	return (cmds);
}

void		parse(t_ms *ms)
{
	t_parser p;

	parse_d(ms);
	p.i = 0;
	p.ignore = 0;
	p.j = 0;
	while (ms->input[p.i])
	{
		if (p.ignore)
			p.i++;
		p.ignore = 0;
		if (ms->input[p.i] == '\\' && ++p.i)
			p.ignore = 1;
		if (ms->input[p.i] && !p.ignore)
		{
			if (ft_strchr("'\"", ms->input[p.i]))
				p.i += quote_handler(ms->input + p.i, 0);
			if (ft_strchr("|;><", ms->input[p.i]))
			{
				make_cmd(ms, p.j, &p.i, ms->input);
				p.j = p.i + 1 + skip_while(ms->input + p.i + 1, ' ');
			}
		}
		if (!p.ignore)
			p.i++;
	}
	if (ms->input[p.j])
	{
		if (!(ms->tab = parse_split(ms->input + p.j, ' ', ms)))
			errex(ms, SPLT_ERR);
		new_cmd(ms, S_COLON, ms->tab);
	}
	ms->lst_end = ms->cmds;
	ms->cmds = get_head(ms->cmds, &ms->cmd_err);
	/* Debug */
	print_cmds(ms->cmds);
	// puts("\nOut of parser2");
}
