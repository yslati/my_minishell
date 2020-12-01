/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:48:45 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/28 20:48:54 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		skip_till(char *s, char *set, int quote_ig)
{
	int i;

	if (*s == '"' && !quote_ig)
		return (-2);
	if (ft_strchr("$\\\" /", *s))
		return (-1);
	i = -1;
	while (s[++i])
		if (ft_strchr(set, s[i]))
			return (i);
	return (i);
}

char	*get_vvalue(char *var_name, char **env)
{
	int		i;
	int		l;

	if ((i = get_env(env, var_name)) < 0)
		return (ft_strdup(""));
	l = ft_strlen(var_name);
	free(var_name);
	return (ft_strdup(env[i] + l + 1));
}

char	*remake_input(char *input, char *varv, int name_len, int *i)
{
	int		l;
	char	*tmp;

	l = ft_strlen(input) - name_len + ft_strlen(varv) - 1;
	tmp = (char *)malloc(l + 1);
	ft_bzero(tmp, l + 1);
	ft_strlcpy(tmp, input, *i);
	ft_strcat(tmp, varv);
	ft_strcat(tmp, input + *i + name_len);
	*i += ft_strlen(varv) - 1;
	free(input);
	free(varv);
	return (tmp);
}

int		replace_var(t_ms *ms, t_parser *p)
{
	if (ms->input[p->i + 1] == '?')
	{
		++p->i;
		p->tmp = ft_itoa(ms->status);
		ms->input = remake_input(ms->input, p->tmp, 1, &p->i);
		return (CONT);
	}
	p->l = skip_till(ms->input + ++p->i, " \"'\\$><|;", p->quote_ig);
	if (p->l == -1)
		return (CONT);
	p->l = (p->l == -2) ? 0 : p->l;
	p->tmp = get_vvalue(ft_strldup(ms->input + p->i, p->l), ms->env);
	ms->input = remake_input(ms->input, p->tmp, p->l, &p->i);
	return (0);
}

void	parse_d(t_ms *ms)
{
	t_parser p;

	init_parser(&p);
	while (ms->input[p.i])
	{
		p.slash_ig = (p.i && ms->input[p.i - 1] != '\\') || !p.i;
		if (ms->input[p.i] == '"' && p.slash_ig)
			p.quote_ig = !p.quote_ig;
		if (p.slash_ig && ms->input[p.i] == '\'' && !p.quote_ig)
			p.i += quote_handler(ms->input + p.i, 0);
		p.slash_ig = (p.i && ms->input[p.i - 1] != '\\') || !p.i;
		if (ms->input[p.i] == '$' && p.slash_ig)
		{
			if (replace_var(ms, &p) == CONT)
				continue ;
		}
		else
			p.i++;
	}
}
