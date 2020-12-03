/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_chars_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 14:52:38 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/30 16:52:12 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		quote_handler(char const *s, int neg)
{
	char	quote;
	int		i;

	i = 1;
	quote = s[0];
	if (quote == '\'')
		while (s[i] && s[i] != quote)
			i++;
	else
		while (s[i] && (s[i] != quote || s[i - 1] == '\\'))
			i++;
	if (!s[i])
	{
		if (!neg)
			return (i - 1);
		else
			return (-1);
	}
	return (i);
}

char	*remove_bslash(char *elem, int i, char *err)
{
	char *tmp;

	if (!elem[i + 1])
	{
		*err = STX_ERR;
		return (elem);
	}
	tmp = ft_strdup(elem);
	tmp[i++] = '\0';
	ft_strcat(tmp, elem + i);
	free(elem);
	return (tmp);
}

char	*catch_bslash(char *elem, t_ms *ms, int j, int *e)
{
	while (elem[++j] && j < *e)
		if (elem[j] == '\\' && ft_strchr("$\"\\", elem[j + 1]))
		{	
			elem = remove_bslash(elem, j, &ms->cmd_err);
			--*e;
			if (elem[j] == '$')
				continue;
		}
	return (elem);
}

char	*remove_quotes(char *elem, int *i, int e, t_ms *ms)
{
	char	*tmp;

	if (elem[*i] == '"')
		elem = catch_bslash(elem, ms, *i, &e);
	tmp = ft_strdup(elem);
	tmp[(*i)++] = '\0';
	ft_strcat(tmp, elem + *i);
	tmp[e - 1] = '\0';
	ft_strcat(tmp, elem + ++e);
	free(elem);
	*i = e - 3;
	return (tmp);
}

char	*parse_quote_bslash(char *elem, t_ms *ms)
{
	int		i;
	int		l;

	i = -1;
	while (elem[++i])
	{
		if (ft_strchr("\"'", elem[i]) && ((i && elem[i - 1] != '\\') || !i))
		{
			if ((l = quote_handler(elem + i, 1)) < 0)
			{
				ms->cmd_err = 1;
				break ;
			}
			elem = remove_quotes(elem, &i, i + l, ms);
			if (i < 0)
				continue ;
		}
		if (elem[i] == '\\')
			elem = remove_bslash(elem, i, &ms->cmd_err);
	}
	return elem;
}
