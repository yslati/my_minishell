/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:23:08 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/15 17:24:24 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean(t_ms *ms)
{
	free(ms->input);
}

void	errex(t_ms *ms, int step)
{
	if (ms->err == STX_ERR)
		ft_putstr_fd("minishell: syntax error", 1);
	else if (ms->err == RDIN_ERR)
		ft_putstr_fd("minishell: reading input error", 1);
	else if (ms->err == SPLT_ERR)
		ft_putstr_fd("minishell: splitting input error", 1);
	if (!step)
		clean(ms);
	minishell(ms->env, step != 0);
}
