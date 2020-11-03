/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:03:01 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/03 12:48:04 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		new_cmd(t_cmd **head, char del, char **tab)
{
	t_cmd	*c;

	if (!(c = (t_cmd*)malloc(sizeof(t_cmd))))
		return ;
	c->cmd = ft_strdup(tab[0]);
	c->args = dup_str_tab(tab);
	if (*head != NULL)
		c->start = ((*head)->end == 1) ? 1 : 0;
	else
		c->start = 1;
	c->end = (del == S_COLON) ? 1 : 0;
	c->prev = *head;
	*head = c;
}

void		init_cmd(t_cmd	*cmd)
{
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->start = 2;
	cmd->end = 2;
	cmd->redir = 0;
	cmd->prev = NULL;
	cmd->next = NULL;
}

void		init(t_ms *ms, char step)
{
	if (!step)
	{
		ms->input = (char *)malloc(SIZE);
	}
	ms->err = 0;
	ms->cmds_count = 0;
	ms->pp_count = 0;
	ms->tab = NULL;
}
