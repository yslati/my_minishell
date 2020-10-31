/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yoo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 09:38:07 by yslati            #+#    #+#             */
/*   Updated: 2020/10/31 11:28:34 by yslati           ###   ########.fr       */
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
            _          _______    _______  _________
|\     /|  ( (    /|  (  ____ \  (  ____ \ \__   __/
| )   ( |  |  \  ( |  | (    \/  | (    \/    ) (
| |   | |  |   \ | |  | (_____   | (__        | |
| |   | |  | (\ \) |  (_____  )  |  __)       | |
| |   | |  | | \   |        ) |  | (          | |
| (___) |  | )  \  |  /\____) |  | (____/\    | |
(_______)  |/    )_)  \_______)  (_______/    )_(

*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void			ft_putstr_fd(char *s, int fd)
{
	if (s)
		while (*s)
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
}

void			ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_print_env(char **env)
{
	int		i = 0;
	if (env)
	{
		while (env[i])
		{
			if (strchr(env[i], '='))
				printf("%s\n", env[i]);
			i++;
		}
	}
}

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

char	*ft_strcpy_pro(char *dst, const char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

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

int				check_exist(char **env, char *arg)
{
	int i;
	char	*wanted;

	wanted = strdup("");
	wanted = ft_strcpy_pro(wanted, arg, '=');
	if ((i = get_env(env, wanted)) != -1)
		return (i);
	return (-1);
}

char			**rm_arr(char **env, int pos)
{
	char 		**arr;
	int			i;
	int			j;
	int			len;

	i = 0;
	j = 0;
	len = arrlen(env) - 1;
	if (!(arr = (char **)malloc(sizeof(char **) * len + 1)))
		return (NULL);
	while (i < len)
	{
		if (j != pos)
			arr[i++] = strdup(env[j]);
		j++;
	}
	arr[i] = NULL;
	return (arr);
}

int				main(int ac, char **av, char **env)
{
	char		*arg;
    char		**arr;
	int			i;

	arg = av[1];
	if (env)
		arr = arrdup(env, arrlen(env));

	
	if (arg)
	{
		if ((strchr(arg, '=')) && (i = check_exist(arr, arg) != -1))
		{
			puts("with");
			// i = check_exist(arr, arg);
			arr = rm_arr(env, i);
			// printf("%d\n", i);
		}
		else if ((i = check_exist(arr, arg)) != -1)
		{
			puts("without");
			i = get_env(env, arg);
			arr = rm_arr(env, i);
			// printf("%d\n", i);
		}
		else
			puts("makinch had l3jb");
	}
	ft_print_env(arr);
	
	return (0);
}
