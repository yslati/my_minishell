/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:03:01 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/03 14:18:49 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parser(t_parser *p)
{
	p->i = 0;
	p->j = 0;
	p->m = 0;
	p->quote_ig = 0;
	p->slash_ig = 0;
	p->l = 0;
}

void	free_cmds(t_ms *ms)
{
	t_cmd *c;
	t_cmd *tmp;

	c = ms->cmds;
	while (c)
	{
		free(c->cmd);
		c->cmd = NULL;
		c->args = free_str_table(c->args);
		tmp = c;
		c = c->next;
		free(tmp);
	}
	ms->cmds = NULL;
	free(ms->input);
	ms->input = NULL;
}

void	init_zero(t_ms *ms, char **env)
{
	int i;

	ms->status = 0;
	ms->input = NULL;
	ms->env = dup_str_tab(env);
	if ((i = check_exist(ms->env, "OLDPWD")) != -1)
	{
		free(ms->env[i]);
		ms->env[i] = ft_strdup("OLDPWD");
	}
	else
		ms->env = add_to_arr("OLDPWD", &ms->env);
	ms->pwd = getcwd(NULL, 0);
	ms->old_pwd = NULL;
	ms->cmd_tab = NULL;
	ms->tab = NULL;
	ms->cmds = NULL;
	ms->ret_status = 0;
	
}

void	init(t_ms *ms, char step, char **env)
{
	ms->err = 0;
	ms->cmd_err = 0;
	ms->redir = 0;
	ms->ctrl = 0;
	ms->pp_count = 0;
	if (!step)
		init_zero(ms, env);
	if (step == 2)
	{
		if (ms->tab)
			ms->tab = free_str_table(ms->tab);
		if (ms->cmd_tab)
			ms->cmd_tab = free_str_table(ms->cmd_tab);
		free_cmds(ms);
	}
}
