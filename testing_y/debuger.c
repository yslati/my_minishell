/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:08:08 by yslati            #+#    #+#             */
/*   Updated: 2020/11/07 09:11:03 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"



/* void    debug_cmd(t_cmd *cmd, int i, int pos, char c)
{
    int j;

    printf("CHAR: %c | POS:%d | I=%d\n", c, pos, i);
    printf("CMD: %s| APPEND: %d\n", cmd->cmd, cmd->append);
    j = 0;
	if (cmd->args)
		while (cmd->args[j]){
			printf("ARG %d: %s|\n--------------------------\n", j, cmd->args[j]);
			j++;
		}
	else
		puts("ARG: No arguments");
} */