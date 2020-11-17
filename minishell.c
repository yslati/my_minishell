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

int		minishell(char **env, int step)
{
	t_ms	*ms;

	ms = (t_ms*)malloc(sizeof(t_ms));
	if (!step)
		init(ms, 0, env);
	while (1)
	{
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m",1);
		parse(ms);
		//puts("1");
		exec_command(ms);
		//puts("2");
		init(ms, 1, NULL);
		//puts("3");
	}
	return (1);
}

int		main(int ac,char **av, char **env)
{
	ac = 0;
	av = NULL;
	minishell(env, 0);
	return(0);
}
