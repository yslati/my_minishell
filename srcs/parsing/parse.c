/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:21:10 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/16 12:36:56 by yslati           ###   ########.fr       */
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

void		get_input(t_ms *ms)
{
	int i;

	if ((i = read(0, ms->input, SIZE)) < 0)
	{
		ms->err = RDIN_ERR;
		errex(ms, 0);
	}
	ms->input[i - 1] = '\0';
}

int			skip_while(char *s, char c)
{
	int i;
	
	i = 0;
	while (s[i] == c)
		++i;
	return (i);
}

void		parse(t_ms *ms)
{
	int		i;
	int		b;

	get_input(ms);
	//printf("INPUT after get_input()==>|%s|\n", ms->input);
	parse_d(ms);
	//printf("INPUT after parse_d()==>|%s|\n", ms->input);
	i = -1;
	b = 0;
	while (ms->input[++i])
	{
		if (ft_strchr("'\"", ms->input[i]) && ((i && ms->input[i - 1] != '\\') || !i))
			i += quote_handler(ms->input + i, 0);
		if (ft_strchr("|;><", ms->input[i]) && ((i && ms->input[i - 1] != '\\') || !i))
		{
			make_cmd(ms, b, &i, ms->input);
			b = i + 1;
		}
	}

	b += skip_while(ms->input + i, ' ');
	if (ms->input[i - 1] != ';')
	{
		if (ms->input[b])
		{
			if (!(ms->tab = parse_split(ms->input + b, ' ', ms)))
				errex(ms, SPLT_ERR);
			new_cmd(ms, S_COLON, ms->tab);
		}
		else if (ms->cmds)
				ms->cmds->is_err = STX_ERR;
		else
				ms->cmd_err = STX_ERR;
	}
	ms->cmds = get_head(ms->cmds);
	//puts("\nWE ARE OUT OF PARSING !");
	//printf("PIPE_COUNT=|%d|\n", ms->pp_count);
	print_cmds(ms->cmds);
}
