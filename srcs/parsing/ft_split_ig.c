/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:58:28 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/04 12:05:37 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		quote_handler(char const *s)
{
	char	quote;
	int		i;

	i = 1;
	quote = s[0];
	while (s[i] && s[i] != quote)
		i++;
	if (!s[i])
		return (i - 1);
	return (i);
}

int		ft_words(char const *s, char c)
{
	int		len;

	len = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s == '\'' | *s == '"')
			s += quote_handler(s);
		if ((*s == ';' || *s == '|') && *(s + 1) != c)
			len++ && ++s;
		if (*s && *s != c && (*(s + 1) == ';' || *(s + 1) == '|'))
			len++;
		if ((*s == c && *(s + 1) != c) || *(s + 1) == '\0')
			len++;
		s++;
	}
	printf("LEN=|%d|\n", len);
	return (len);
}

char	**ft_exception(char const *s)
{
	char	**tab;

	tab = NULL;
	if (!s)
	{
		tab = (char **)malloc(1 * sizeof(char *));
		tab[0] = NULL;
	}
	return (tab);
}

char	**free_everything(char **tab, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int		ft_len_elem(char const *s, char c)
{
	int		i;
	int		size;
	int		ret;

	i = -1;
	size = 0;
	while (s[++i] && s[i] != c)
	{
		if (s[i] == '\'' | s[i] == '"')
		{
			ret = quote_handler(s + i);
			size += ret;
			i += ret;
		}
		if (*s == ';' || *s == '|')
		{
			size++;
			break ;
		}
		if (s[i] != c)
			size++;
		if (s[i] && s[i] != c && (s[i + 1] == ';' | s[i + 1] == '|'))
			break ;
	}
	return (size);
}

char	*quote_filling(char *s, char *quote, int *i, char *elem)
{
	if (*s == '\'' | *s == '"')
	{
		*quote = *s;
		elem[(*i)++] = *s++;
		while (*s && *s != *quote)
			elem[(*i)++] = *s++;
		if (*s)
			elem[(*i)++] = *s++;
	}
	return (s);
}

char	*fill_elem(char *elem, char *s, char c)
{
	int		i;
	char	quote;

	i = 0;
	while (*s && *s != c)
	{
		quote = 0;
		s = quote_filling(s, &quote, &i, elem);
		if (*s == ';' || *s == '|')
		{
			elem[i++] = *s++;
			break ;
		}
		if (*s && !quote)
			elem[i++] = *s++;
		if (*s && *s != c && (*(s + 1) == ';' | *(s + 1) == '|'))
		{
			elem[i++] = *s++;
			break ;
		}
	}
	elem[i] = '\0';
	return (s);
}

char	**ft_split_ig(char const *s, char c)
{
	char	**tab;
	int		j;
	int		l;

	if ((tab = ft_exception(s)))
		return (tab);
	l = ft_words(s, c);
	j = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (l + 1))))
		return (NULL);
	tab[l] = NULL;
	while (j < l)
	{
		while (*s && *s == c)
			s++;
		if (!(tab[j] = (char *)malloc((ft_len_elem(s, c) + 1) * sizeof(char))))
			return (free_everything(tab, l));
		s = fill_elem(tab[j++], (char *)s, c);
	}
	return (tab);
}
