/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 12:46:10 by yslati            #+#    #+#             */
/*   Updated: 2020/11/29 12:46:10 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				is_set(char *target, char *set)
{
	int			i;
	int			j;
	int			b;

	if (!target || !*target || !set)
		return (0);
	j = -1;
	while (target[++j])
	{
		b = 0;
		i = -1;
		while (set[++i])
			if (target[j] == set[i])
				b = 1;
		if (!b)
			return (0);
	}
	return (1);
}

void			exit_analyse(t_ms *ms, int *b)
{
	if (!is_set(ms->cmds->args[1], "0123456789"))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(ms->cmds->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ms->ret_status = 255;
	}
	else if (is_set(ms->cmds->args[1], "0123456789"))
	{
		if (ms->tab[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			*b = 0;
		}
		else
			ms->ret_status = ft_atoi(ms->cmds->args[1]);
	}
}

void			free_parsing_struct(t_ms *ms)
{
	ms->env = free_str_table(ms->env);
	ms->tab = free_str_table(ms->tab);
	ms->cmd_tab = free_str_table(ms->cmd_tab);
	free_cmds(ms);
	free(ms->pwd);
	free(ms->old_pwd);
	if (ms->ctrl == CTRL_D)
		free(ms->input);
	free(ms);
}

int				ft_exit(t_ms *ms)
{
	int			b;

	ft_putendl_fd("exit", 1);
	if (!ms->ctrl)
	{	
		b = 1;
		if (ms->cmds->args[1])
			exit_analyse(ms, &b);
		if (!b && (ms->status = 1))
			return (1);
	}
	b = ms->ret_status;
	free_parsing_struct(ms);
	exit(b);
}
