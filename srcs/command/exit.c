/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:01:34 by obouykou          #+#    #+#             */
/*   Updated: 2020/06/08 16:01:34 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				is_set(char *target, char *set)
{
	int	i;
	int j;
	int	b;

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
		ft_putendl_fd(": numeric argument required", 2);	
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
	free_str_table(ms->tab, tb_len(ms->tab));
	free_str_table(ms->cmd_tab, tb_len(ms->cmd_tab));
	free_cmds(ms);
	free(ms);
}

int				ft_exit(t_ms *ms)
{
	int	b;

	ft_putendl_fd("exit", 1);
	b = 1;
	if (ms->cmds->args[1])
		exit_analyse(ms, &b);
	if (ms->env)
		free_str_table(ms->env, tb_len(ms->env));
	b = ms->ret_status;
	free_parsing_struct(ms);
	exit(ms->ret_status);
	return (0);
}
