/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:03:01 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/31 12:29:14 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		init_cmd(t_cmd	*cmd)
{
	cmd->cmds = NULL;
	cmd->args = NULL;
	cmd->start = 2;
	cmd->end = 2;
	cmd->redir = 0;
	cmd->file = NULL;
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
	ms->pp_count = 0;
	ms->tab = NULL;
}
