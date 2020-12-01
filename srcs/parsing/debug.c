/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:30:38 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/29 13:44:42 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	print_total_cmds(char **cmds_tab)
{	
	/* Debugging */
	FILE *f;
	f = fopen("/Users/yslati/Desktop/minishell_yo/debug", "w+");
	print_tab(cmds_tab, "Cmds_Table", f);
	fclose(f);
	/* End_Debugging */
}

void		print_tab(char **tab, char *tab_name, FILE *f)
{
	int i;
	
	if (f != NULL)
	{
		fprintf(f, "\n%s length = |%d|\n", tab_name, tb_len(tab));
		if (!tab)
			fprintf(f, "\n%s is NULL\n", tab_name);
		else
		{
			fprintf(f, "\n%s\n\n", tab_name);
			if (tab[0] == NULL)
				fprintf(f, "\t%s[%d] = |%s|",tab_name, 0, tab[0]);
			i = -1;
			while (tab[++i])
				fprintf(f, "\t%s[%d] = |%s|", tab_name, i, tab[i]);
		}
	}
	//else
	//	printf("FILE DESCRIPTOR IS NULL\n");
}


void		print_cmds(t_cmd *cmds)
{
	FILE *fd;

	fd = fopen("/Users/yslati/Desktop/minishell_yo/debug", "a+");
	if (fd)
	{
		if (cmds == NULL)
			fputs("\nERROR: ==> cmds is NULL\n", fd);
		while (cmds)
		{
			fprintf(fd,"\n\n===================================\n\n==> CMD=|%s|\n", cmds->cmd);
			print_tab(cmds->args, "CMD_ARGS", fd);
			fprintf(fd, "\n\nStart=|%d|\tEnd=|%d|\tRedir=|%c|%d|\tErr=|%d|\n", 
						cmds->start, cmds->end, cmds->redir, cmds->redir, cmds->is_err);
			cmds = cmds->next;
		}
	}
	//else
	//	printf("FILE DESCRIPTOR IS NULL\n");
	fclose(fd);
}
