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

int		is_set(char *target, char *set)
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

void		exit_analyse(t_ms *ms, int *b, int *r)
{
	if (!is_set(ms->tab[1], "0123456789"))
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(ms->tab[1], 1);
		ft_putendl_fd(": numeric argument required", 1);	
	}
	else if (is_set(ms->tab[1], "0123456789"))
	{
		if (ms->tab[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 1);
			*b = 0;
		}
		else
			*r = ft_atoi(ms->tab[1]);
	}
}

void		ft_exit(t_ms *ms)
{
	int r;
	int	b;

	ft_putendl_fd("exit", 1);
	b = 1;
	r = ms->ret;
	if (ms->tab[1])
		exit_analyse(ms, &b, &r);
	if (ms->tab)
		free_str_table(ms->tab, tb_len(ms->tab));
	if (b == 1)
		exit(r);
}
