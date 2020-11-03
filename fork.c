/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:00:49 by yslati            #+#    #+#             */
/*   Updated: 2020/11/02 11:34:01 by yslati           ###   ########.fr       */
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

/* #define   MAX_COUNT  200
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
} */

/* ----------------------------------------------------------------- */
/* PROGRAM fork-02.c                                                 */
/*   This program runs two processes, a parent and a child.  Both of */
/* them run the same loop printing some messages.  Note that printf()*/
/* is used in this program.                                          */
/* ----------------------------------------------------------------- */

#include  <stdio.h>
#include  <sys/types.h>

#define   MAX_COUNT  200

void			ChildProcess(void);                /* child process prototype  */
void			ParentProcess(void);               /* parent process prototype */

int				main(void)
{
     pid_t  pid;

     pid = fork();
     if (pid == 0) 
          ChildProcess();
     else 
          ParentProcess();
}

void			ChildProcess(void)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
          printf("   This line is from child, value = %d\n", i);
     printf("   *** Child process is done ***\n");
}

void			ParentProcess(void)
{
     int   i;

     for (i = 1; i <= MAX_COUNT; i++)
          printf("This line is from parent, value = %d\n", i);
     printf("*** Parent is done ***\n");
}


