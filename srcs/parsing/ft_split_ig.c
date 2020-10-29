/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 22:07:02 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/29 09:28:52 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*quote_handler(char const *s)
{
	char	quote;

	quote = *s++;
	while (*s && *s != quote)
		s++;
	if (!*s)
		return (NULL);
	return (s);
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
		{
			s = quote_handler(s);
		}
		if (*s && (*s == c && *(s + 1) != c) || *(s + 1) == '\0')
			len++;
		s++;
	}
	return (len);
}

int		ft_len_elem(char const *s, char c)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		size++;
	}
	return (size);
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

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
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
		i = 0;
		while (*s && *s != c)
			tab[j][i++] = *s++;
		tab[j++][i] = '\0';
	}
	return (tab);
}
