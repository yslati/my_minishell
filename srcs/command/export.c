/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:23:28 by yslati            #+#    #+#             */
/*   Updated: 2020/11/07 09:23:56 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


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

void			sort_env(char **env)
{
	int			i;
	char		*str;
	char		*tmp;
	char		**arr;

	i = 0;
	arr = arrdup(env, arrlen(env));
	if (arr)
		ft_sort_arr(arr);
	while (arr[i])
	{
		str = (char *)malloc(sizeof(char) * (ft_strlen(arr[i]) + 15));
		str = ft_strcpy(str, "declare -x ");
		tmp = ft_strdup("");
		tmp = ft_strcpy_pro(tmp, arr[i], '=');
		str = ft_strcat(str, tmp);
		if ((tmp = ft_strchr(arr[i], '=')))
		{
			str = ft_strcat(str, "=\"");
			str = ft_strcat(str, tmp + 1);
			str = ft_strcat(str, "\"");
			str = ft_strcat(str, "\0");
		}
		ft_putendl_fd(str, 1);
		i++;
	}
}

int			ft_export(t_ms *ms, char **env)
{
	int i;

	i = 0;
	if (env)
		i = + 1 - 1;
		// ms->env = arrdup(env, arrlen(env));
	if (!ms->cmds->args[1])
		sort_env(ms->env);
	else if (ft_strchr(ms->cmds->args[1], '='))
	{
		// puts("add to ENV");
		if ((i = check_exist(ms->env, ms->cmds->args[1])) != -1)
		{
			// puts("kayn in ENV");
			(ms->env[i]) ? free(ms->env[i]) : 0;
			ms->env[i] = ms->cmds->args[1];
		}
		else
		{
			// puts("makinch in ENV");
			ms->env = add_to_arr(ms->cmds->args[1], ms->env);
			//ft_print_env(ms->env);
		}
	}
	else
	{
		// puts("without = ");
		ms->env = add_to_arr(ms->cmds->args[1], ms->env);
		//ft_print_env(ms->env);
	}
	return 0;
}
