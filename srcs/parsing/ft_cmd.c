/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:10:59 by obouykou          #+#    #+#             */
/*   Updated: 2020/06/08 16:10:59 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void		ft_cmd(t_ms *ms)
{
	if (ms->tab[0] == NULL)
		return ;
	if (!ft_strcmp(ms->tab[0], "exit"))
		ft_exit(ms);
	else if (!ft_strcmp(ms->tab[0], "echo"))
		ft_echo(ms);
	else
	{
		ft_putstr_fd(ms->tab[0], 1);
		ft_putendl_fd(": command not found", 1);
	}
}
