/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:04:34 by yslati            #+#    #+#             */
/*   Updated: 2020/11/26 11:19:38 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				cmp_get_pos(char **env, char *var)
{
	int i;

	i = -1;
	if (env)
		while (env[++i])
			if ((!ft_strcmp(env[i], var)))
				return (i);
	return (get_env(env, var));
}

int				check_exist(char **env, char *arg)
{
	int i;
	char	*wanted;

	wanted = ft_strdup("");
	wanted = ft_strcpy_pro(wanted, arg, '=');
	if (((i = get_env(env, wanted)) != -1))
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
	len = tb_len(env) - 1;
	if (!(arr = (char **)malloc(sizeof(char **) * len + 1)))
		return (NULL);
	while (i < len)
	{
		if (j != pos)
			arr[i++] = ft_strdup(env[j]);
		j++;
	}
	arr[i] = NULL;
	return (arr);
}

int         ft_unset(t_ms *ms)
{
	int i;
	int len;

	len = 0;
	i = 1;
	while (ms->cmds->args[i])
	{
		if (ft_strchr(ms->cmds->args[i], '=') || !valid_arg(ms->cmds->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(ms->cmds->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
		else if ((len = cmp_get_pos(ms->env, ms->cmds->args[i])) != -1)
			ms->env = rm_arr(ms->env, len);
		i++;
	}
	return (0);
}
