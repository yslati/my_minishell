/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:04:48 by yslati            #+#    #+#             */
/*   Updated: 2020/11/13 09:58:24 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int         ft_cd(t_ms *ms)
{
	int i;
	int x;

	i = 0;
	x = 0;
	// puts("wa l3alwa");
	if (!ms->cmds->args[1] || !ft_strcmp(ms->cmds->args[1], "~"))
	{
		i = get_env(ms->env, "HOME");
		chdir(ms->env[i] + 5);
	}
	else if (!ft_strcmp(ms->cmds->args[1], "-"))
	{
		if ((i = get_env(ms->env, "OLDPWD")) != -1)
			chdir(ms->env[i] + 7);
		else
		{
			x = 1;
			ft_putendl_fd("cd: OLDPWD not set", 1);
		}
	}
	else if (ms->cmds->args[1] != NULL)
		if (chdir(ms->cmds->args[1]) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(ms->cmds->args[1], 1);
			ft_putendl_fd(": No such file or directory", 1);
		}
	if (x == 0)
	{
		ms->env = set_env("OLDPWD", ms->pwd, ms->env);
		ms->pwd = getcwd(NULL, 0);
		ms->env = set_env("PWD", ms->pwd, ms->env);
	}
	return (0);
}
