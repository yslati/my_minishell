/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:05:17 by yslati            #+#    #+#             */
/*   Updated: 2020/11/23 13:01:45 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int			ft_error(t_ms *ms, int err)
{
	if (err == STX_ERR)
		ft_putstr_fd("minishell: syntax error", 1);
	else
	{	
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(ms->cmds->cmd, 1);
		if (err == 2)
			ft_putstr_fd(": No such file or directory\n", 1);
		else if (err == 4)
			ft_putstr_fd(": command not found\n", 1);
		//else if 

	}
	exit(0);
	return (0);
}
