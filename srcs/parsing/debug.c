/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:30:38 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/16 09:05:29 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		print_tab(char **tab, FILE *f)
{
	int i;

	i = -1;
//	fprintf(f, "\n**ARGS Tab length = |%d|\n", tb_len(tab));
	if (f != NULL)
	{
		if (!tab)
			fputs("\nARGS TAB is NULL\n", f);
		else
		{
			if (tab[0] == NULL)
				fprintf(f, "\tARG[%d] = |%s|", 0, tab[0]);
			while (tab[++i])
				fprintf(f, "\tARG[%d] = |%s|", i, tab[i]);
		}
	}
	else
	{
		if (!tab)
			puts("\nARGS TAB is NULL\n");
		else
		{
			if (tab[0] == NULL)
				printf("\tARG[%d] = |%s|", 0, tab[0]);
			while (tab[++i])
				printf("\tARG[%d] = |%s|", i, tab[i]);
		}
	}
}

t_cmd		*get_head(t_cmd *cmds)
{
	while (cmds && cmds->prev)
		cmds = cmds->prev;
	return (cmds);
}

void		print_cmds(t_cmd *cmds)
{
	FILE *f;
	f = fopen("/Users/yslati/Desktop/minishell_yo/debug", "w+");
	if (cmds == NULL)
		fputs("\nERROR: ==> cmds is NULL\n", f);
	while (cmds)
	{
		fprintf(f,"\n==> CMD=|%s|\n\nARGS:\n", cmds->cmd);
		print_tab(cmds->args, f);
		fprintf(f, "\nStart=|%d|\tEnd=|%d|\tRedir=|%c|%d|\tErr=|%d|\tStatus=|%d|\n", 
					cmds->start, cmds->end, cmds->redir, cmds->redir, cmds->is_err, cmds->is_status);
		cmds = cmds->next;
	}
	fclose(f);
}
