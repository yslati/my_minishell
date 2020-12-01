/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:56:00 by yslati            #+#    #+#             */
/*   Updated: 2020/11/30 14:21:58 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				is_builtin_sys(char *cmds)
{
	if (ft_strcmp(cmds, "env") && ft_strcmp(cmds, "cd") &&
		ft_strcmp(cmds, "pwd") && ft_strcmp(cmds, "export") &&
		ft_strcmp(cmds, "unset") && ft_strcmp(cmds, "echo") &&
		ft_strcmp(cmds, "exit"))
		return (0);
	return (1);
}

int				*dup_in_out(t_ms *ms)
{
	if (ms->j != 0)
		if (dup2(ms->fds[ms->j - 2], 0) < 0)
		{
			perror("dup2");
			exit(1);
		}
	if (ms->cmds->next && (ms->pp_count || !ms->cmds->end))
		if (dup2(ms->fds[ms->j + 1], 1) < 0)
		{
			perror("dup2");
			exit(1);
		}
	return (ms->fds);
}

pid_t			run_child(t_ms *ms, int i)
{
	pid_t		pid;
	t_cmd		*tmp;

	tmp = ms->cmds;
	pid = fork();
	if (pid == 0)
	{
		if (ms->pp_count)
			ms->fds = dup_in_out(ms);
		if (ms->cmds->redir)
			ft_redir(ms, tmp, ms->cmds);
		while (ms->pp_count && i < 2 * ms->pp_count)
			close(ms->fds[i++]);
		if (ms->cmds->args && (!is_builtin_sys(ms->cmds->cmd)
			|| ms->cmds->redir) && check_command(ms))
		{
			cmd_error(ms, CMD_NOT_FOUND_ERR, NULL, ms->cmds->cmd);
			exit(127);
		}
		exit(0);
	}
	if (ms->pp_count)
		ms->tpid[ms->j / 2] = pid;
	return (pid);
}

t_ms			*exucte_help(t_ms *ms)
{
	while (ms && ms->cmds->redir)
	{
		if (!ms->cmds->next)
			break ;
		ms->cmds = ms->cmds->next;
	}
	return (ms);
}

t_cmd			*exucte_cmd(t_ms *ms)
{
	while (ms->cmds)
	{
		if ((ms->cmds->start == 0 && ms->cmds->prev->redir)
			|| (ms->cmds->start && is_builtin_sys(ms->cmds->cmd)
			&& (!ms->cmds->redir && !ms->pp_count)))
			break ;
		ms->pid = run_child(ms, 0);
		ms = exucte_help(ms);
		if (ms->pid < 0)
		{
			perror("Fork error"); /* ======================= */
			exit(0);
		}
		if (ms->cmds->end)
			break ;
		else
			ms->cmds = ms->cmds->next;
		ms->j += 2;
	}
	return (ms->cmds);
}

int				wait_child(t_ms *ms)
{
	int			st;
	int			i;

	st = 0;
	i = -1;
	if (!ms->pp_count)
		waitpid(ms->pid, &st, 0);
	else
	{
		while (++i < ms->pp_count + 1)
		{
			waitpid(ms->tpid[i], &st, 0);
			if (st == 2)
				return (2);
		}
	}
	return (st);
}

void			manage_cmd(t_ms *ms)
{
	int			st;
	int			i;

	st = 0;
	i = 0;
	save_fds(ms->backup);
	ms->cmds = exucte_cmd(ms);
	restore_fds(ms->backup);
	while (ms->pp_count && i < 2 * ms->pp_count)
		close(ms->fds[i++]);
	st = wait_child(ms);
	if (st == 2 || st == 3)
		ms->status = st + 128;
	else
		ms->status = (st >> 8) & 255;
}

void			exec_command(t_ms *ms)
{
	int			i;

	i = 0;
	(ms->pp_count) ? ms->fds = (int *)malloc((2 * ms->pp_count) * sizeof(int)) : 0;
	(ms->pp_count) ? ms->tpid = (pid_t *)malloc(sizeof(pid_t) * (ms->pp_count + 1)) : 0;
	while (ms->pp_count && i < 2 * ms->pp_count)
	{
		pipe(ms->fds + i * 2);
		i++;
	}
	ms->j = 0;
	while (ms->cmds)
	{
		if ((ms->cmds->next && !ms->cmds->end) || !is_builtin_sys(ms->cmds->cmd))
			manage_cmd(ms);
		if (is_builtin_sys(ms->cmds->cmd))
			check_command(ms);
		ms->cmds = ms->cmds->next;
	}
}

char			*get_exec_path(t_ms *ms)
{
	int			i;
	char		**tab;
	char		*path;
	struct stat	stats;

	if ((i = get_env(ms->env, "PATH")) != -1)
	{
		tab = ft_split(ms->env[i] + 5, ':');
		i = -1;
		while (tab[++i])
		{
			path = ft_strjoin(tab[i], "/");
			path = ft_strjoin(path, ms->cmds->cmd);
			if ((stat(path, &stats)) == 0)
				if (stats.st_mode & X_OK)
					return (path);
		}
	}
	else
	{
		cmd_error(ms, F_NOT_FOUND_ERR, NULL, ms->cmds->cmd);
		exit (127);
	}
	return (NULL);
}

void			check_command_help(t_ms *ms)
{
	char		*path;

	path = NULL;
	if (ms->cmds->cmd[0] == '/' || (ms->cmds->cmd[0] == '.' && ms->cmds->cmd[1] == '/') || ft_strchr(ms->cmds->cmd, '/'))
	{
		if (execve(ms->cmds->cmd, ms->cmds->args, ms->env) < 0)
		{
			if (ft_strchr(ms->cmds->cmd, '/'))
				cmd_error(ms, F_NOT_FOUND_ERR, NULL, ms->cmds->cmd);
			else
				cmd_error(ms, CMD_NOT_FOUND_ERR, NULL, ms->cmds->cmd);
			exit(127);
		}
	}
	else if (!is_builtin_sys(ms->cmds->cmd))
	{
		path = get_exec_path(ms);
		(path) ? execve(path, ms->cmds->args, ms->env) : 0;
		(path) ? free(path) : 0;
	}
}

int				check_command(t_ms *ms)
{
	int			ret;

	ret = 1;
	if (!ft_strcmp(ms->cmds->cmd, "cd"))
		ret = ft_cd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "pwd"))
		ret = ft_pwd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "env"))
		ret = ft_env(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "export"))
		ret = ft_export(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "unset"))
		ret = ft_unset(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "echo"))
		ret = ft_echo(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "exit"))
		ft_exit(ms);
	else
		check_command_help(ms);
	return (ret);
}
