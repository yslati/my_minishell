/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:25:14 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/30 13:10:46 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			get_env(char **env, char *var)
{
	int		i;
	char	*search;

	search = (char *)malloc(sizeof(char) * (ft_strlen(var) + 2));
	i = 0;
	search = ft_strcpy(search, var);
	search = ft_strcat(search, "=");
	while (env && env[i++])
		if (!(ft_strncmp(env[i], search, ft_strlen(search))))
		{
			free(search);
			return (i);
		}
	free(search);
	return (-1);
}

char		**get_arr(char *value, char **env)
{
	char	**arr;
	int		i;

	i = tb_len(env) + 2;
	if (!(arr = (char **)malloc(sizeof(char *) * i)))
		return (NULL);
	i = 0;
	while (env[i])
	{
		arr[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		arr[i] = env[i];
		i++;
	}
	arr[i] = value;
	arr[i + 1] = NULL;
	return (arr);
}

char		**add_to_arr(char *value, char **env)
{
	char	**new_arr;

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

char		**set_env(char *var, char *value, char **env)
{
	int		i;
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

int			ft_env(t_ms *ms)
{
	int		i;

	i = -1;
	if (!ms->cmds->args[1])
	{
		while (ms->env && ms->env[++i])
			if (ft_strchr(ms->env[i], '='))
				ft_putendl_fd(ms->env[i], 1);
	}
	else
	{
		cmd_error(ms, F_NOT_FOUND_ERR, "env", ms->cmds->args[1]);
		ms->status = 127;
		return (1);
	}
	return (0);
}
