/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 11:11:49 by yslati            #+#    #+#             */
/*   Updated: 2020/11/29 14:00:34 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			check_n(char **args, int *i)
{
	int		nflag;

	nflag = 0;
	while (!ft_strncmp(args[*i], "-n", 2))
	{
		*i = *i + 1;
		nflag = 1;
	}
	return (nflag);
}

int			ft_echo(t_ms *ms)
{
	int		i;
	int		nflag;

	i = 1;
	nflag = 0;
	if (!ms->cmds->args[i])
		ft_putendl_fd("", 1);
	else if (ms->cmds->args[i])
	{
		nflag = check_n(ms->cmds->args, &i);
		while (ms->cmds->args[i])
		{
			ft_putstr_fd(ms->cmds->args[i], 1);
			if (ms->cmds->args[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
		if (!nflag)
			ft_putchar_fd('\n', 1);
	}
	ms->status = 0;
	return (0);
}
