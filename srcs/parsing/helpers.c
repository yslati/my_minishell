/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:04:11 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/28 12:11:21 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			skip_while(char *s, char c)
{
	int i;
	
	i = 0;
	while (s[i] == c)
		++i;
	return (i);
}

int		tb_len(char **table)
{
	int len;

	len = 0;
	if (table)
		while (table[len])
			++len;
	return (len);
}

char	**free_str_table(char **tab, int size)
{
	if (!tab)
		return (NULL);
	while (size--)
	{
		free(tab[size]);
		tab[size] = NULL;
	}
	free(tab);
	return (NULL);
}

char	**dup_str_tab(char **arr)
{
	int		l;
	char	**tab;

	l = tb_len(arr);
	if (!(tab = (char **)malloc((l + 1) * sizeof(char *))))
		return(NULL);
	tab[l] = NULL;
	while (--l >= 0)
		tab[l] = ft_strdup(arr[l]);
	return (tab);
}
