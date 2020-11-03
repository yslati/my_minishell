/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:21:10 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/03 12:49:52 by obouykou         ###   ########.fr       */
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
	if (!(ms->tab = parse_split(tmp, ' '))) // need free 
		errex(ms, SPLT_ERR);
	free(tmp);
	b = i;
}

void		parse_scolon_pp(t_ms *ms, int b, int i, char *s)
{
	ms->cmds_count++;
	if (s[i] == S_COLON)
		parse_scolon(ms, b, i, ms->input);
	else if (s[i] == PIPE)
		parse_pipe(ms, b, i, ms->input);
	new_cmd(&ms->cmds, s[i], ms->tab);
	free(ms->tab);
	ms->tab = NULL;
	puts("\n=======> PARSE COLON/PIPE DONE !\n");
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
		if (is_from(ms->input[i], "|;"))	
		{
			parse_scolon_pp(ms, b, i, ms->input);
			b = i + 1;
		}
	if (!ms->tab && ++ms->cmds_count)
		ms->tab = parse_split(ms->input + b, ' ');
	print_cmds(ms->cmds);
}
