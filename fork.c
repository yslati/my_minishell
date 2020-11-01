/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:00:49 by yslati            #+#    #+#             */
/*   Updated: 2020/11/01 10:18:40 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <unistd.h>

/* 
 _____ ___  ____  _  __
|  ___/ _ \|  _ \| |/ /
| |_ | | | | |_) | ' / 
|  _|| |_| |  _ <| . \ 
|_|   \___/|_| \_\_|\_\

 */

void		fork_exp()
{
	int x = 1;
	
	if (fork() == 0)
		printf("hello from child x = %d\n", ++x);
	else
		printf("hello from parent x = %d\n", --x);
}

int			main(int ac, char **av, char **env)
{
	// fork();
	// fork();
	// fork();
	// printf("meao meaaaao\n");

	fork_exp();

	return (0);
}