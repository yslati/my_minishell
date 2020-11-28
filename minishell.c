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
	int 	i;

	ms = (t_ms*)malloc(sizeof(t_ms));
	if (!step)
		init(ms, 0, env);
	while (1)
	{
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m",1);
		if (parse_total_cmds(ms))
		{
			ft_putstr_fd("minishell: syntax error\n", 1);
			free_str_table(ms->cmd_tab, tb_len(ms->cmd_tab));
			ms->cmd_tab = NULL;
			init(ms, 1, NULL);
			continue ;
		}
		if (ms->cmd_tab)
		{
			i = -1;
			while(ms->cmd_tab[++i])
			{
				ms->input = ms->cmd_tab[i];
				parse(ms);
				if (ms->cmd_err || (ms->lst_end && !ms->lst_end->end))
				{
					// puts("parser2");
					ft_putstr_fd("minishell: syntax error\n", 1);
					free_str_table(ms->cmd_tab, tb_len(ms->cmd_tab));
					ms->cmd_tab = NULL;
					break ;
				}
				// puts("\nNow command");
				exec_command(ms);
				free_cmds(ms);
			}
		}
		init(ms, 2, NULL);
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
