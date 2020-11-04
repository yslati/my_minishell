/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:25:14 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/04 13:07:26 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		ret[i] = ft_strdup(arr[i]);
	ret[i] = NULL;
	return (ret);
}

int			get_env(char **env, char *var)
{
	int 	i;
	char	*search;

	search = (char *)malloc(sizeof(char) * (ft_strlen(var) + 2));
	i = 0;
	search = ft_strcpy(search, var);
	search = ft_strcat(search, "=");
	if (env)
	{
		while (env[i])
		{
			if (!(ft_strncmp(env[i], search, ft_strlen(search))))
				return (i);
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
		arr[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
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
	len = ft_strlen(var) + ft_strlen(value) + 2;
	if (!(line = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	line = ft_strcpy(line, var);
	line = ft_strcat(line, "=");
	line = ft_strcat(line, value);
	if ((i = get_env(env, var)) != -1)
	{
		(env[i]) ? free(env[i]) : 0;
		env[i] = line;
	}
	else
		return (add_to_arr(line, env));
	return (env);
}

void	ft_print_env(char **env)
{
	int		i = 0;
	if (env)
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '='))
				printf("%s\n", env[i]);
			i++;
		}
	}
}

int			ft_env(t_ms *ms, char **env)
{
    int		i;

    i = 0;
	if (env)
		ms->env = arrdup(env, arrlen(env));
	if (!ms->cmds->args[1])
		ft_print_env(ms->env);
	else
	{
		ft_putstr_fd("env: ", 1);
		ft_putstr_fd(ms->cmds->args[1], 1);
		ft_putendl_fd(": No such file or directory", 1);
		return (0);
	}
	return (1);
}
