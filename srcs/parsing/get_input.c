// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   get_input.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/06/08 14:05:23 by obouykou          #+#    #+#             */
// /*   Updated: 2020/06/08 14:05:23 by obouykou         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// void		print_tab(char **tab)
// {
// 	int i;

// 	i = -1;
// 	while (tab[++i])
// 		printf("TAB[%d] = |%s|\n", i, tab[i]);
// }


// t_list		*ft_lstnew(void *content)
// {
// 	t_list	*l;

// 	if (!(l = (t_list*)malloc(sizeof(t_list))))
// 		return (NULL);
// 	l->content = content;
// 	l->next = NULL;
// 	return (l);
// }

// /* int			cmd_len(char **tab, int i)
// {
// 	t_cmd	n_cmd;

// 	i = -1;
// 	while (tab[++i])
// 	{
		
// 	}
// } */

// int			is_from(char c, char *set)
// {
// 	if (set)
// 		while (*set)
// 		{
// 			if (*set++ == c)
// 				return (1);
// 		}
// 	return (0);
// }

// char		check_stx(char *s, t_ms *ms, char *c)
// {
// 	char			sp;
// 	int				i;
// 	static	int		n_rdr;

// 	if (*s == *c || (is_from(*s, "><") && is_from(*c, "><")))
// 	{
// 		printf("Special element repeated !\n");
// 		return (1);
// 	}
// 	i = -1;
// 	*c = 0;
// 	n_rdr = 0;
// 	printf("Beg ===> s= |%s|\tn_rdr= |%d|\tc= |%c|\n\n", s, n_rdr, *c);
// 	while (s[++i])
// 	{
// 		if (s[i] == '\'' || s[i] == '"')
// 		{
// 			n_rdr = 0;
// 			sp = s[i++];
// 			while (s[i] && s[i] != sp)
// 				i++;
// 			if (!s[i])
// 				return (sp);
// 		}
// 		if (s[i] == '|' || s[i] == ';')
// 		{
// 			n_rdr = 0;
// 			ms->pp_count += (s[i] == '|');
// 			*c = s[i];
// 			printf("s= |%s|\tn_rdr= |%d|\tc= |%c|\n\n", s + i, n_rdr, *c);
// 			if (s[i + 1] == s[i])
// 				return (1);
// 		}
// 		if (s[i] == '>' || s[i] == '<')
// 		{
// 			n_rdr++;
// 			*c = s[i];
// 			if ((s[i + 1] == *c && *c != '>') || (*c == '>' && s[ i + 1] == '<') || n_rdr > 2)
// 				return (1);
// 		}
// 		else
// 			n_rdr = 0;
// 	}
// 	return (0);
// }

// void		test_input(t_ms *ms, char **tab)
// {
// 	int		i;
// 	char	c;

// 	i = -1;
// 	while (tab[++i] && tab[i][0])
// 	{
// 		check_stx(tab[i], ms, &c);
// 		if (c && (!tab[i + 1] || !tab[i + 1][0]))
// 		{
// 			printf("TAB[%i]= |%s|\tc= |%c|\n\n", i,tab[i], c);
// 			ms->err = STX_ERR;
// 			return ;
// 		}
// 		if (is_from(c, "|><") && (!tab[i + 1] || !tab[i + 1][0]))
// 		{
// 			ms->err = STX_ERR;
// 			return ;
// 		}
// 	}
// }

// void		parse_in(t_ms *ms)
// {
// 	int n;
	
// 	n = read(0, ms->input, SIZE);
// 	ms->input[n - 1] = 0;
// 	if ((ms->tab = ft_split_ig(ms->input, ' ')) == NULL)
// 	{
// 		ft_putendl_fd("Error : splitting error !", 1);
// 		exit(1);
// 	}

// 	/* Debug */
// 	print_tab(ms->tab);
// 	puts("\n");
	
// 	test_input(ms, ms->tab);
// 	if (ms->err == STX_ERR)
// 	{
// 		ft_putstr_fd("minishell: syntax error", 1);
// 		return ;
// 	}
// 	//test_input(ms, ms->tab);
// }
