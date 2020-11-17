/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:23:28 by yslati            #+#    #+#             */
/*   Updated: 2020/11/14 12:26:42 by yslati           ###   ########.fr       */
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
	arr = dup_str_tab(env);
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

int 		valid_arg(t_ms *ms, int i)
{
	int j;

	j = 0;
	if (!ft_isalpha(ms->cmds->args[i][0]))
		return (0);
	while (ft_isalnum(ms->cmds->args[i][++j]) && ms->cmds->args[i][j])
		;
	return (ms->cmds->args[i][j] == '\0');
}

int			ft_export(t_ms *ms)
{
	int i;
	int len;

	i = 1;
	len = 0;
	if (!ms->cmds->args[i])
		sort_env(ms->env);
	else
	while (ms->cmds->args[i])
	{
		if (!valid_arg(ms, i))
		{
			ft_putstr_fd("minishell: export: `", 1);	
			ft_putstr_fd(ms->cmds->args[i++], 1);	
			ft_putstr_fd("': not a valid identifier\n", 1);
			continue;	
		}
		if (ft_strchr(ms->cmds->args[i], '='))
		{
			if ((len = check_exist(ms->env, ms->cmds->args[i])) != -1)
			{
				(ms->env[len]) ? free(ms->env[len]) : 0;
				ms->env[len] = ms->cmds->args[i];
			}
			else
				ms->env = add_to_arr(ms->cmds->args[i], ms->env);
		}
		else if ((cmp_get_pos(ms->env, ms->cmds->args[i])) == -1)
				ms->env = add_to_arr(ms->cmds->args[i], ms->env);
		i++;
	}
	return 0;
}
