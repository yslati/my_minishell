/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 09:35:39 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/26 09:35:39 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void		minishell(char **env)
{
	t_ms ms;

	env[tb_len(env) - 1] = NULL;
	init(&ms, 0);
	while (1)
	{
		init(&ms, 1);
		ft_putstr_fd("\033[1;31m\n$minishell$~> \033[0m",1);
		parse_in(&ms);
		if (!ft_strcmp(ms.tab[0], "clear") || !ft_strcmp(ms.tab[0], "cl"))
			ft_putstr_fd("\e[1;1H\e[2J",1);
		//ft_cmd(&ms);
	}
}

int		main(int ac,char **av, char **env)
{
	ft_putstr_fd("\e[1;1H\e[2J",1);
	ac = 0;
	av = NULL;
	minishell(env);
	return(0);
}