/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:30:38 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/03 12:44:57 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		print_tab(char **tab)
{
	int i;

	i = -1;
	if (!tab)
		puts("\nTAB is NULL\n");
	if (tab)
		while (tab[++i])
			printf("\tTAB[%d] = |%s|\n", i, tab[i]);
}

t_cmd		*get_head(t_cmd *cmds)
{
	if (cmds)
	{
		puts("\nERROR: ==> cmds is NULL\n");
		return(NULL);
	}
	while (cmds && cmds->prev)
		cmds = cmds->prev;
	return (cmds);
}

void		print_cmds(t_cmd *cmds)
{
	cmds = get_head(cmds);
	while (cmds)
	{
		printf("\n==> CMD=|%s|\n\nARGS:\n", cmds->cmd);
		print_tab(cmds->args);
		printf("\n S=|%d| E=|%d| Redir=|%d|\n", cmds->start, cmds->end, cmds->redir);
	}
}