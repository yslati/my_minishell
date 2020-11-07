/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:03:01 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/07 09:27:31 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		new_cmd(t_ms *ms, char del, char **tab)
{
	t_cmd	*c;

	if (!(c = (t_cmd*)malloc(sizeof(t_cmd))))
		return ;
	c->next = NULL;
	c->cmd = ft_strdup(tab[0]);
	c->args = dup_str_tab(tab);
	//if (ms->redir != 0)
	c->redir = ms->redir;
	if (ms->cmds != NULL)
		c->start = (ms->cmds->end == 1) ? 1 : 0;
	else
		c->start = 1;
	c->end = (del == S_COLON) ? 1 : 0;
	if (ms->cmds)
		ms->cmds->next = c;
	c->prev = ms->cmds;
	ms->cmds = c;
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
	ms->err = 0;
	ms->cmds_count = 0;
	ms->pp_count = 0;
	ms->cmds = NULL;
	ms->redir = 0;
	if (step)
	{
		free_str_table(ms->tab, tb_len(ms->tab));
		ms->tab = NULL;
	}

	/* REMOVE STEP IF NOT NEEDED */
	step = 1;
}
