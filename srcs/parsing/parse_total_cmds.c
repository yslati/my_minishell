/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_total_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:21:10 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/25 09:23:43 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int		get_hm_cmds(char *input, t_parser *p)
{
	int		r;

	p->i = 0;
	p->j = 0;
	p->l = 0;
	p->ignore = 0;
	p->m = 0;
	while (input[p->i])
	{
		if (p->ignore)
			p->i++;
		p->ignore = 0;
		if (input[p->i] == '\\' && ++p->i)
			p->ignore = 1;
		if (!p->ignore)
		{
			if (input[p->i] && ft_strchr("'\"", input[p->i]))
			{
				if ((r = quote_handler(input + p->i, 1)) < 0)
					return (-1);
				p->i += r;
			}
			if (input[p->i] == ';')
			{
				p->j = p->i + 1;
				p->m = p->j + skip_while(input + p->j, ' ');
				if (input[p->m] == ';')
					return (-1);
				p->l++;
			}
		}
		if (!p->ignore)
			p->i++;
	}
	if (input[p->m])
		p->l++;
	return (p->l);
}

int		parse_total_cmds(t_ms *ms)
{
	t_parser p;

	get_input(ms);
	if (ms->input[0] == '\0')
	{
		return (0);
	}
	if (get_hm_cmds(ms->input, &p) < 0)
	{
		free(ms->input);
		ms->input =	NULL;
		return (STX_ERR);
	}
	ms->cmd_tab = (char **)malloc(sizeof(char *) * (p.l + 1));
	p.i = -1;
	p.j = 0;
	p.ti = 0;
	ms->cmd_tab[p.l] = NULL;
	while (ms->input[++p.i])
	{
		if (ft_strchr("'\"", ms->input[p.i]) && ((p.i && ms->input[p.i - 1] != '\\') || !p.i))
			p.i += quote_handler(ms->input + p.i, 1);
		if (';' == ms->input[p.i] && ((p.i && ms->input[p.i - 1] != '\\') || !p.i))
		{
			ms->cmd_tab[p.ti++] = ft_substr(ms->input, p.j, p.i - p.j + 1);
			p.j = p.i + 1 + skip_while(ms->input + p.i + 1, ' ');
		}
	}
	if (ms->input[p.j])
		ms->cmd_tab[p.ti] = ft_substr(ms->input, p.j, p.i - p.j + 1);
	free(ms->input);
	ms->input = NULL;
	/* Debugging */
	FILE *f;
	f = fopen("/Users/yslati/Desktop/minishell_yo/debug", "w+");
	print_tab(ms->cmd_tab, "Cmds_Table", f);
	fclose(f);
	/* End_Debugging */
	// puts("\nOut of parser1");
	return (ms->cmd_err);
}
