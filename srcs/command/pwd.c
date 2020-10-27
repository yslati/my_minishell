/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:03:38 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/27 14:06:10 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			get_dir(t_ms *ms)
{
	if (ms->path[0] != 0)
	{
		//ft_strcpy(ms->old_path, ms->path);
		ft_bzero(ms->path, sizeof(ms->path));
	}
	if ((ms->path = getcwd(NULL, 0)) == NULL)
		ft_putendl_fd("PWD error", 1);
	else
	{
		ft_putendl_fd(ms->path, 1);
		ms->old_path = ms->path;
		return (1);
	}
	return (0);
}

