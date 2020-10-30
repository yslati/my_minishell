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
		ft_putstr_fd("\n$minishell$~> ", 1);
		parse_in(&ms);
		//ft_cmd(&ms);
	}
}

int		main(int ac,char **av, char **env)
{
	ac = 0;
	av = NULL;
	minishell(env);
	return(0);
}