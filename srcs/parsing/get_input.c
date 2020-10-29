/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 14:05:23 by obouykou          #+#    #+#             */
/*   Updated: 2020/06/08 14:05:23 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		print_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		printf("TAB[%d] = |%s|\n", i, tab[i]);
}

void		test_input(t_ms *ms, char *in)
{
	ms->pp_count = char_counter(in, '|');
}

void		parse_in(t_ms *ms)
{
	int n;
	
	n = read(0, ms->input, SIZE);
	ms->input[n - 1] = 0;
	test_input(ms, ms->input);
	if ((ms->tab = ft_split(ms->input, ' ')) == NULL)
	{
		ft_putendl_fd("Error : splitting error !", 1);
		exit(1);
	}
	print_tab(ms->tab);
}
