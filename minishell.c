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

void		parse_exec(t_ms *ms)
{
	int		i;

	if (parse_total_cmds(ms))
	{
		clean_stx_err(ms);
		init(ms, 1, NULL);
		return ;
	}
	if (ms->cmd_tab)
	{
		i = -1;
		while (ms->cmd_tab[++i])
		{
			signal(SIGQUIT, handle_sig);
			ms->input = ms->cmd_tab[i];
			parse(ms);
			if (ms->cmd_err || (ms->lst_end && !ms->lst_end->end))
			{
				clean_stx_err(ms);
				break ;
			}
			exec_command(ms);
			free_cmds(ms);
		}
	}
	init(ms, 2, NULL);
}
void		handle_sig(int sig)
{
	t_ms		ms;

	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m", 1);
	}
	else if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", 2);
		kill(ms.pid, sig);
	}
}

int			minishell(char **env, int step)
{
	t_ms	*ms;

	ms = (t_ms*)malloc(sizeof(t_ms));
	if (!step)
		init(ms, 0, env);
	while (1)
	{
		signal(SIGQUIT,SIG_IGN);
		if (ms->status != 130)
			ft_putstr_fd("\033[1;31m$minishell$~> \033[0m", 1);
		parse_exec(ms);
	}
	return (0);
}


int			main(int ac, char **av, char **env)
{
	ac = 0;
	av = NULL;

	signal(SIGINT, handle_sig);
	minishell(env, 0);
	return (0);
}
