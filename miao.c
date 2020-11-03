/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miao.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:32:04 by yslati            #+#    #+#             */
/*   Updated: 2020/11/03 14:28:43 by yslati           ###   ########.fr       */
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
 _______            _______   _______   _______  _________
(  ____ \ |\     /| (  ____ ) (  ___  ) (  ____ ) \__   __/
| (    \/ ( \   / ) | (    )| | (   ) | | (    )|    ) (   
| (__      \ (_) /  | (____)| | |   | | | (____)|    | |   
|  __)      ) _ (   |  _____) | |   | | |     __)    | |   
| (        / ( ) \  | (       | |   | | | (\ (       | |   
| (____/\ ( /   \ ) | )       | (___) | | ) \ \__    | |   
(_______/ |/     \| |/        (_______) |/   \__/    )_(   

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

/* int				arrlen(char **arr)
{
	int 	i;
	
	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
			i++;
	}
	return (i);
} */

/* char			**arrdup(char **arr, int len)
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
} */

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

/* int			get_env(char **env, char *var)
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
} */

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

/* ================== */

int        ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] == s2[i])
    {
        if (!s1[i] && !s2[i])
            return (0);
        i++;
    }
    return (s1[i] - s2[i]);
}

void    ft_sort_wordtab(char **tab)
{
    int			i;
    int			chng;
    char		*tmp;

    chng = 1;
    while (chng)
    {
        chng = 0;
        i = 0;
        while (tab[i + 1])
        {
            if (ft_strcmp(tab[i], tab[i + 1]) > 0)
            {
                tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
                chng = 1;
            }
            i++;
        }
    }
}

/* ===================== */

void			sort_env(char **env)
{
	int			i;
	char		*str;
	char		*tmp;

	i = 0;
	if (env)
		ft_sort_wordtab(env);
	while (env[i])
	{
		str = (char *)malloc(sizeof(char) * (strlen(env[i]) + 14));
		str = strcpy(str, "declare -x ");
		tmp = strdup("");
		tmp = ft_strcpy_pro(tmp, env[i], '=');
		str = strcat(str, tmp);
		if ((tmp = strchr(env[i], '=')))
		{
			str = strcat(str, "=\"");
			str = strcat(str, tmp + 1);
			str = strcat(str, "\"");
			str = strcat(str, "\0");
		}
		
		ft_putendl_fd(str, 1);
		i++;
	}
}

int				main(int ac, char **av, char **env)
{
    char		*arg;
    char		**arr;
	int			i;

	arg = av[1];
	if (env)
		arr = arrdup(env, arrlen(env));


	if (!arg)
	{
		// puts("sort env");
		sort_env(arr);
	}
	else if (strchr(arg, '='))
	{
		// puts("add to ENV");
		if ((i = check_exist(arr, arg)) != -1)
		{
			// puts("kayn in ENV");
			printf("%s\n",arr[i]);
			(arr[i]) ? free(arr[i]) : 0;
			arr[i] = arg;
			printf("%s\n",arr[i]);
		}
		else
		{
			// puts("makinch in ENV");
			arr = add_to_arr(arg, arr);
			ft_print_env(arr);
		}
		
		// printf("arg: %s\n", arg);
		// printf("i : %d\n", i);
		// printf(" ===> %s\n",ft_strcpy_pro(str, arg, '='));
	}
	else
	{
		// puts("without = ");
		arr = add_to_arr(arg, arr);
		ft_print_env(arr);
	}
	return (0);
}