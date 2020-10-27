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

	//parse(av);
	env[0] = NULL;
	while (1)
	{
		init(&ms);
		ft_putstr_fd("$minishell$~> ", 1);
		get_input(&ms);
		ft_cmd(&ms);
	}
}

int		main(int ac,char **av, char **env)
{
	if (ac && av[0])
	{
		print_tab(env);
	}
	exit(0);
	minishell(env);
	return(0);
}