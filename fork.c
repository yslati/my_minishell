/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:00:49 by yslati            #+#    #+#             */
/*   Updated: 2020/11/02 08:47:40 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/types.h>

/*
 _____ ___  ____  _  __
|  ___/ _ \|  _ \| |/ /
| |_ | | | | |_) | ' / 
|  _|| |_| |  _ <| . \ 
|_|   \___/|_| \_\_|\_\

 */

/* void		fork_exp()
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
} */

#define   MAX_COUNT  200
#define   BUF_SIZE   100

int			main(void)
{
     pid_t  pid;
     int    i;
     char   buf[BUF_SIZE];

     fork();
     pid = getpid();
     for (i = 1; i <= MAX_COUNT; i++) {
          sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
          write(1, buf, strlen(buf));
     } 
}


