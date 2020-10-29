/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teting.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:38:41 by yslati            #+#    #+#             */
/*   Updated: 2020/10/29 14:35:18 by yslati           ###   ########.fr       */
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

char			**arrdup(char **arr, int len)
{
	char 	**ret;
	int 	i;

	i = -1;
	if (!(ret = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (++i < len)
		ret[i] = strdup(arr[i]);
	ret[i] = NULL;
	return (ret);
}

/* void			ft_err_msg(char *cmd, int err, char *arg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
} */

int		ft_isprint(int c)
{
	return (c <= 126 && c >= 32);
}

/* int			my_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && )
} */

int			get_env(char **env, char *var)
{
	int 	i;
	char	*search;

	search = (char *)malloc(sizeof(char) * (strlen(var) + 2));
	i = 0;
	search = strcpy(search, var);
	search = strcat(search, "=");
	if (env)
	{
		while (env[i])
		{
			if (!(strncmp(env[i], search, strlen(search))))
			{
				return (i);
			}
			i++;
		}
	}
	return (-1);
}

char	**get_arr(char *value, char **env)
{
	char	**arr;
	int		len;
	int		i;
	
	i = 0;
	len = arrlen(env) + 2;
	if (!(arr = (char **)malloc(sizeof(char *) * len)))
		return (NULL);
	while(env[i])
	{
		arr[i] = (char *)malloc(sizeof(char) * (strlen(env[i]) + 1));
		arr[i] = env[i];
		i++;
	}
	arr[i] = value;
	arr[i + 1] = NULL;
	return (arr);
}

char	**add_to_arr(char *value, char **env)
{
	int i;
	int len;
	char **new_arr;

	i = 0;
	len = arrlen(env);	
	if (env == NULL)
	{
		new_arr = (char **)malloc(sizeof(char *) * 2);
		new_arr[0] = value;
		new_arr[1] = NULL;
	}
	else
		return (get_arr(value, env));
	return (new_arr);
}

char	**set_env(char *var, char *value, char **env)
{
	int 	i;
	size_t	len;
	char	*line;
	
	i = 0;
	len = strlen(var) + strlen(value) + 2;
	if (!(line = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	line = strcpy(line, var);
	line = strcat(line, "=");
	line = strcat(line, value);
	if ((i = get_env(env, var)) != -1)
	{
		(env[i]) ? free(env[i]) : 0;
		env[i] = line;
	}
	else
	{
		return (add_to_arr(line, env));
	}
	return (env);
}

void	ft_print_env(char **env)
{
	int		i = 0;
	if (env)
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}

int main(int ac, char **av, char **env)
{
/*========= ===  == cd ==  === =========*/
	/* printf("%s\n", getcwd(NULL, 0));
	chdir(av[1]);
	printf("%s\n", getcwd(NULL, 0)); */
	
/*===================== ENV =======================*/

	char	*path;
	char	*pwd;
	int		i = 0;
	// int		i = 0;
	// int		err = 2;
	char **arr;

	if (env)
	{
		arr = arrdup(env, arrlen(env));
		// if (av[1] == NULL)
		// {
		// 	while (arr[i] != NULL)
		// 	{
		// 		ft_putendl_fd(arr[i], 1);
		// 		i++;
		// 	}
		// }
		// else if (av[1])
		// 	ft_err_msg(av[0], err, av[1]);
	}
	path = av[1];
	pwd = getcwd(NULL, 0);
	if (path == NULL || !strcmp(av[1], "/Users/yslati"))
	{
		i = get_env(env, "HOME");
		chdir(env[i] + 5);
	}
	else if (!strcmp(path, "-"))
	{
		if ((i = get_env(env, "OLDPWD")) != -1)
			chdir(env[i] + 7);
		else
			printf("cd: OLDPWD not set\n");		
	}
	else if (path != NULL)
	{
		if (chdir(path) != 0)
			puts("Error");
	}
	arr = set_env("OLDPWD", pwd, arr);
	pwd = getcwd(NULL, 0);
	arr = set_env("PWD", pwd, arr);
	puts("here");
	if (!(ft_strcmp(av[1], "env")))
	{
		puts("jjjj");
		ft_print_env(arr);
	}
	return (0);
}
