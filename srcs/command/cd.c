/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:04:48 by yslati            #+#    #+#             */
/*   Updated: 2020/11/30 12:45:55 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		set_oldpwd(t_ms *ms)
{
	ms->env = set_env("OLDPWD", ms->pwd, ms->env);
	ms->pwd = getcwd(NULL, 0);
	ms->env = set_env("PWD", ms->pwd, ms->env);
}

int			ft_cd(t_ms *ms)
{
	int i;
	int is;

	i = 0;
	is = 0;
	if (!ms->cmds->args[1] || !ft_strcmp(ms->cmds->args[1], "~"))
	{
		if ((i = get_env(ms->env, "HOME")) < 0)
			cmd_error(ms, HOME_NOT_SET_ERR, NULL, "cd");
		else
			chdir(ms->env[i] + 5);
	}
	else if (!ft_strcmp(ms->cmds->args[1], "-"))
	{
		if ((i = get_env(ms->env, "OLDPWD")) != -1)
			chdir(ms->env[i] + 7);
		else
			is = cmd_error(ms, OLDPWD_ERR, "cd", NULL);
	}
	else if (ms->cmds->args[1] != NULL)
		if (chdir(ms->cmds->args[1]) != 0)
			is = cmd_error(ms, F_NOT_FOUND_ERR, "cd", ms->cmds->args[1]);
	if (is == 0)
		set_oldpwd(ms);
	return (0);
}
