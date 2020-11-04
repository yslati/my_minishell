/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:23:28 by yslati            #+#    #+#             */
/*   Updated: 2020/11/04 14:46:02 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void    ft_sort_wordtab(char **tab)
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

void			sort_env(char **env)
{
	int			i;
	char		*str;
	char		*tmp;

	i = 0;
	if (env)
		ft_sort_arr(env);
	while (env[i])
	{
		str = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 14));
		str = ft_strcpy(str, "declare -x ");
		tmp = ft_strdup("");
		tmp = ft_strcpy_pro(tmp, env[i], '=');
		str = ft_strcat(str, tmp);
		if ((tmp = ft_strchr(env[i], '=')))
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
		ms->env = arrdup(env, arrlen(env));
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
