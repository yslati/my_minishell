/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:23:28 by yslati            #+#    #+#             */
/*   Updated: 2020/12/03 11:43:15 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*ft_strcpy_pro(char *dst, const char *src, char c)
{
	int		i;

	i = -1;
	while (src[++i] != c)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

void		sort_env(char **env)
{
	int		i;
	char	*pos;
	char	*str;
	char	*tmp;
	char	**arr;

	i = -1;
	arr = dup_str_tab(env);
	if (arr)
	{	
		ft_sort_arr(arr);
		while (arr[++i])
		{
			if ((pos = ft_strchr(arr[i], '=')))
			{
				str = (char *)malloc(sizeof(char) * (ft_strlen(arr[i]) + 14));
				tmp = ft_strldup(arr[i], pos - arr[i]);
			}
			else
			{
				str = (char *)malloc(sizeof(char) * (ft_strlen(arr[i]) + 12));
				tmp = ft_strdup(arr[i]);
			}
			str = ft_strcpy(str, "declare -x ");
			str = ft_strcat(str, tmp);
			if (pos)
			{
				str = ft_strcat(str, "=\"");
				str = ft_strcat(str, pos + 1);
				str = ft_strcat(str, "\"");
			}
			ft_putendl_fd(str, 1);
			tmp = ft_free(tmp);
			str = ft_free(str);
		}
		arr = free_str_table(arr);
	}
}

int			valid_arg(char *arg)
{
	int		j;

	j = 0;
	if (!ft_isalpha(arg[0]))
		return (0);
	while (arg[++j] && arg[j] != '=')
		if (!ft_isalnum(arg[j]))
			return (0);
	return (1);
}

int			export_help(t_ms *ms, int i)
{
	int		len;

	len = 0;
	if ((len = check_exist(ms->env, ms->cmds->args[i])) != -1 ||
		(len = cmp_get_pos(ms->env, ms->cmds->args[i])) != -1)
	{
		free(ms->env[len]);
		ms->env[len] = ft_strdup(ms->cmds->args[i]);
	}
	else
		ms->env = add_to_arr(ms->cmds->args[i], &ms->env);
	return (i);
}

int			ft_export(t_ms *ms)
{
	int		i;

	i = 1;
	if (!ms->cmds->args[i])
		sort_env(ms->env);
	else
		while (ms->cmds->args[i])
		{
			if (!valid_arg(ms->cmds->args[i]))
			{
				cmd_error(ms, NOT_VALID_ERR, "export", ms->cmds->args[i++]);
				continue;
			}
			if (ft_strchr(ms->cmds->args[i], '='))
				i = export_help(ms, i);
			else if ((cmp_get_pos(ms->env, ms->cmds->args[i])) == -1)
				ms->env = add_to_arr(ms->cmds->args[i], &ms->env);
			i++;
		}
	return (0);
}
