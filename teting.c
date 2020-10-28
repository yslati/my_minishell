/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teting.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:38:41 by yslati            #+#    #+#             */
/*   Updated: 2020/10/28 14:06:28 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include <string.h>
# include <stdlib.h>
#include <errno.h>
# include <fcntl.h>
#include  <dirent.h>
#include "libft/libft.h"

/*

db   dD   .d88b.    db        .o88b.  db   db  d888888b   
88 ,8P'  .8P  Y8.   88       d8P  Y8  88   88    `88'     
88,8P    88    88   88       8P       88ooo88     88      
88`8b    88    88   88       8b       88~~~88     88      
88 `88.  `8b  d8'   88booo.  Y8b  d8  88   88    .88.     
YP   YD   `Y88P'    Y88888P   `Y88P'  YP   YP  Y888888P

.88b  d88.    d88888D    db    db    .d8b.     d8b   db 
88'YbdP`88    YP  d8'    `8b  d8'   d8' `8b    888o  88 
88  88  88       d8'      `8bd8'    88ooo88    88V8o 88 
88  88  88      d8'         88      88~~~88    88 V8o88 
88  88  88     d8' db       88      88   88    88  V888 
YP  YP  YP    d88888P       YP      YP   YP    VP   V8P   

*/

int				arrlen(char **arr)
{
	int 	i;
	
	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
			i++;
	}
	return (i);
}

char			**arrdup(char **arr)
{
	char 	**ret;
	int 	len;
	int 	i;

	i = -1;
	len = arrlen(arr);
	if (!(ret = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (++i < len)
		ret[i] = ft_strdup(arr[i]);
	ret[i] = NULL;
	return (ret);
}

void			ft_err_msg(char *cmd, int err, char *arg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
}

int main(int ac, char **av, char **env)
{
/*========= ===  == cd ==  === =========*/
	/* printf("%s\n", getcwd(NULL, 0));
	chdir(av[1]);
	printf("%s\n", getcwd(NULL, 0)); */
	
/*===================== ENV =======================*/


	int		i = 0;
	int		err = 2;
	/* if (env)
	{
		if (av[1] == NULL)
		{
			while (env[i] != NULL)
			{
				ft_putendl_fd(env[i], 1);
				i++;
			}
		}
		else if (av[1])
			ft_err_msg(av[0], err, av[1]);
	} */
	
	char **arr;
	arr = arrdup(env);
	while (arr[i] != NULL)
	{
		ft_putendl_fd(arr[i], 1);
		i++;
	}
	
	return (0);
}
