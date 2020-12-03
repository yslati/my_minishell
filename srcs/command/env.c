/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:25:14 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/03 11:42:27 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			get_env(char **env, char *var)
{
	int		i;
	int		l;
	char	*search;

	l = ft_strlen(var) + 1;
	search = (char *)malloc(sizeof(char) * (l + 1));
	search = ft_strcpy(search, var);
	var = ft_free(var);
	search = ft_strcat(search, "=");
	i = -1;
	if (env)
		while (env[++i])
			if (!(ft_strncmp(env[i], search, l)))
			{
				search = ft_free(search);
				return (i);
			}
	search = ft_free(search);
	return (-1);
}

char		**get_arr(char *value, char ***env)
{
	char	**arr;
	int		i;

	i = tb_len(*env) + 2;
	if (!(arr = (char **)malloc(sizeof(char *) * i)))
		return (NULL);
	i = -1;
	while (env[0][++i])
		arr[i] = ft_strdup(env[0][i]);
	arr[i] = ft_strdup(value);
	arr[i + 1] = NULL;
	*env = free_str_table(*env);
	return (arr);
}

char		**add_to_arr(char *value, char ***env)
{
	char	**new_arr;

	if (*env == NULL)
	{
		new_arr = (char **)malloc(sizeof(char *) * 2);
		new_arr[0] = ft_strdup(value);
		new_arr[1] = NULL;
		return (new_arr);
	}
	else
		return (get_arr(value, env));
}

char		**set_env(char *var, char *value, char ***env)
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
	if ((i = get_env(*env, var)) != -1)
	{
		free(env[0][i]);
		env[0][i] = line;
	}
	else
		return (add_to_arr(line, env));
	return (*env);
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
