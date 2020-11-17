/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:48:45 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/15 20:41:17 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		skip_till(char *s, char *set, int inside_dquote)
{
	int i;

	if (*s == '"' && !inside_dquote)
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

void	parse_d(t_ms *ms)
{
	int i;
	int l;
	char inside_dquote;

	i = 0;
	inside_dquote = 0;
	while (ms->input[i])
	{
		if (ms->input[i] == '"' && ((i && ms->input[i - 1] != '\\') || !i))
			inside_dquote = !inside_dquote;
		if (((i && ms->input[i - 1] != '\\') || !i) && ms->input[i] == '\'' && !inside_dquote)
				i += quote_handler(ms->input + i, 0);
		if (ms->input[i] == '$' && ((i && ms->input[i - 1] != '\\') || !i))
		{
			if (ms->input[i + 1] == '?' && i++)
				continue ;
			l = skip_till(ms->input + ++i, " \"'\\$><|;", inside_dquote);
			if (l == -1)
				continue ;
			l = (l == -2)? 0 : l;
			ms->input = remake_input(ms->input, get_vvalue(ft_strldup(ms->input + i, l), ms->env), l, &i);
		}
		else
			i++;
	}
}
