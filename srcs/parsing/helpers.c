/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:04:11 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/03 11:02:30 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		char_counter(char *s, char c)
{
	int n;

	if (!s)
		return (0);
	n = 0;
	while (*s)
		if (*s++ == c)
			n++;
	return (n);
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
		free(tab[size]);
	free(tab);
	return (NULL);
}

char	**dup_str_tab(char **arr)
{
	int		l;
	char	**tab;

	l = tb_len(arr);
	if (!(tab = (char **)malloc((l + 1) * sizeof(char *))))
	tab[l] = NULL;
	while (--l <= 0)
		tab[l] =arr[l];
	return (tab);
}
		