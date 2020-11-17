/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:03:01 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/16 10:11:30 by obouykou         ###   ########.fr       */
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
	c->redir = ms->redir;
	if (ms->cmds != NULL)
		c->start = (ms->cmds->end == 1) ? 1 : 0;
	else
		c->start = 1;
	c->end = (del == S_COLON) ? 1 : 0;
	if (ms->cmds)
		ms->cmds->next = c;
	c->prev = ms->cmds;
	c->is_err = ms->cmd_err != 0;
	c->is_status = ms->status;
	ms->cmds = c;
}

void	free_cmds(t_ms *ms)
{
	t_cmd *c;

	c = ms->cmds;
	while (c)
	{
		free(c->cmd);
		c->cmd = NULL;
		free_str_table(c->args, tb_len(c->args));
		c = c->next;
	}
	if (c)
		free(ms->cmds);
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

void		init(t_ms *ms, char step, char **env)
{
	ms->err = 0;
	ms->cmd_err = 0;
	ms->cmds = NULL;
	ms->redir = 0;
	ms->pp_count = 0;
	ms->status = 0;
	if (step)
	{
		free_str_table(ms->tab, tb_len(ms->tab));
		ms->tab = NULL;
		free_cmds(ms);
	}
	if (!step)
	{
		ms->input = (char *)malloc(SIZE);
		ms->env = dup_str_tab(env);
		ms->pwd = getcwd(NULL, 0);
	}
}
