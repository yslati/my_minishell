/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:05:17 by yslati            #+#    #+#             */
/*   Updated: 2020/11/27 10:34:53 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int			ft_error(t_ms *ms, int err)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == STX_ERR && (ms->ret_status = 258))
		ft_putstr_fd("syntax error", 2);
	else
	{	
		ft_putstr_fd(ms->cmds->cmd, 2);
		if (err == F_NOT_FOUND_ERR && (ms->ret_status = 1))
			ft_putstr_fd(": No such file or directory\n", 2);
		else if (err == CMD_NOT_FOUND_ERR && (ms->ret_status = 127))
			ft_putstr_fd(": command not found\n", 2);
	}
	return (0);
}
