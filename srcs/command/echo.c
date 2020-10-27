/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 15:41:35 by obouykou          #+#    #+#             */
/*   Updated: 2020/06/08 15:41:35 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		find_input(t_ms *ms)
{
	char *p;

	p = ms->input + 4;
	while(*p == ' ')
		p++;
	p += (ms->is_op == 1) ? 2 : 0;
	while(*p == ' ')
		p++;
	ms->ptr = p;
}

int			echo_analyse(t_ms *ms)
{
	int i;

	i = 1;
	if (!ft_strcmp(ms->tab[i], "-n"))
	{
		ms->is_op = 1;
		i++;
	}
	find_input(ms);
	if (ms->ptr[0])
		return (1);
	return (0);
}

/* yachamssa l3achiyaaaaaaaaaa  */

void		build_output(t_ms *ms)
{
	int		i;

	i = -1;
	while (ms->ptr[++i])
	{
		if (ms->ptr[i] == 28 && ms->ptr[i - 1] != 28)
			i++;
		ms->output[i] = ms->ptr[i];
	}
	ms->output[i] = 0;
}


/* void		quotes_hundler(t_ms *ms)
{mak
	ms
} */

void		ft_echo(t_ms *ms)
{
	if (ms->tab[1])
		if (echo_analyse(ms) == 0)
		{
			(ms->is_op != 1) ? ft_putchar_fd('\n', 1) : 0;
			return ;
		}
	if (ft_strchr(ms->ptr, '"') == NULL && ft_strchr(ms->ptr, 39) == NULL) /* 39 = ' */
	{
		build_output(ms);
		ft_putstr_fd(ms->output, 1);
	}
	else
	{
		//quotes_handler(ms);
		//ft_putstr_fd(ms->output, 1);
	}
	(ms->is_op != 1) ? ft_putchar_fd('\n', 1) : 0;
}
 