/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:23:28 by yslati            #+#    #+#             */
/*   Updated: 2020/11/03 14:28:36 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int				check_exist(char **env, char *arg)
{
	int i;
	char	*wanted;

	wanted = ft_strdup("");
	wanted = ft_strcpy_pro(wanted, arg, '=');
	if ((i = get_env(env, wanted)) != -1)
		return (i);
	return (-1);
}

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
