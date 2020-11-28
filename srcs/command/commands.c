/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:56:00 by yslati            #+#    #+#             */
/*   Updated: 2020/11/27 12:11:13 by yslati           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int 	is_builtin_sys(char *cmds)
{
	if (ft_strcmp(cmds, "env") && ft_strcmp(cmds, "cd") &&
		ft_strcmp(cmds, "pwd") && ft_strcmp(cmds, "export") &&
		ft_strcmp(cmds, "unset") && ft_strcmp(cmds, "echo") &&
		ft_strcmp(cmds, "exit"))	
		return 0;
	return (1);
}

int			open_file(t_cmd *tmp)
{
	int 	fd;

	fd = 1;
	if (tmp->redir == TRUNC)
		fd = open(tmp->next->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmp->redir == APPEND)
		fd = open(tmp->next->cmd, O_WRONLY | O_CREAT | O_APPEND, 0666);
	return (fd);
}

void			read_file(t_cmd *tmp)
{
	int fd;

	fd = open(tmp->next->cmd, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void			save_fds(int *fds)
{
	fds[0] = dup(0);
	fds[1] = dup(1);
	fds[2] = dup(2);
}

void			restore_fds(int *fds)
{
	dup2(fds[0], 0);
	close(fds[0]);
	dup2(fds[1], 1);
	close(fds[1]);
	dup2(fds[2], 2);
	close(fds[2]);
}

void			ft_redir(t_cmd *tmp, t_cmd *cmd)
{
	int 	i;
	int 	fd_in;

	while (tmp && tmp->redir)
	{
		if (tmp->redir == TRUNC || tmp->redir == APPEND)
		{
			i = 1;
			if (tb_len(tmp->next->args) > 1 && !tmp->next->start)
				while (tmp->next->args[i])
					cmd->args =  get_arr(tmp->next->args[i++], cmd->args);
			fd_in = open_file(tmp);
		}
		else if (tmp->redir == READ)
			read_file(tmp);
		tmp = tmp->next;
	}
	dup2(fd_in, 1);
	close(fd_in);
}

int		*dup_in_out(t_ms *ms)
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

pid_t			run_child(t_ms *ms)
{
	pid_t	pid;
	int i;
	t_cmd	*tmp;
	
	tmp = ms->cmds;
	pid = fork();
	if (pid == 0)
	{
		if (ms->pp_count)
			ms->fds = dup_in_out(ms);
		if (ms->cmds->redir)
			ft_redir(tmp, ms->cmds);
		i = 0;
		while (ms->pp_count && i < 2 * ms->pp_count)
			close(ms->fds[i++]);
		if (ms->cmds->args && check_command(ms) && !is_builtin_sys(ms->cmds->cmd))
			ft_error(ms, CMD_NOT_FOUND_ERR);
		exit(0);
	}
	return (pid);
}

t_ms		*exucte_help(t_ms *ms)
{
	while (ms && ms->cmds->redir)
	{
		if (!ms->cmds->next)
			break;
		ms->cmds = ms->cmds->next;
	}
	return (ms);
}

t_cmd		*exucte_cmd(t_ms *ms)
{
	while(ms->cmds)
	{
		if ((ms->cmds->start == 0 && ms->cmds->prev->redir)
			|| (ms->cmds->start && is_builtin_sys(ms->cmds->cmd)
			&& (!ms->cmds->redir && !ms->pp_count)))
			break ;
		ms->pid = run_child(ms);
		ms = exucte_help(ms);
		if (ms->pid < 0)
		{
			perror("Fork error");
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
	int		st;
	int		i;

	st = 0;
	i = -1;
	if (!ms->pp_count)
		waitpid(ms->pid, &st, 0);
	else
	{
		while (++i < ms->pp_count + 1)
			wait(&st);
		//printf("2 - |%d|\n", st);
	}
	return (st);
}

void			exec_command(t_ms *ms)
{
	int		st = 0;
	ms->skip = 0;
	int		i;
	
	i = 0;
	(ms->pp_count) ? ms->fds = (int *)malloc((2 * ms->pp_count)*sizeof(int)) : 0;
	while (ms->pp_count && i < 2 * ms->pp_count)
	{
		pipe(ms->fds + i * 2);
		i++;
	}
	ms->j = 0;
	while (ms->cmds)
	{
		if (*ms->cmds->cmd == '\0')
			ft_error(ms, CMD_NOT_FOUND_ERR);
		if ((ms->cmds->next && !ms->cmds->end) || (!is_builtin_sys(ms->cmds->cmd)))
		{
			save_fds(ms->backup);
			ms->cmds = exucte_cmd(ms);
			restore_fds(ms->backup);
			i = 0;
			while (ms->pp_count && i < 2 * ms->pp_count)
				close(ms->fds[i++]);
			st = wait_child(ms);
			if (st == 2 || st == 3)
				ms->skip = st + 128;
			else
			{
				ms->skip = (st >> 8) & 255;
			}
			//printf("%d\n", ms->skip);
		}
		if (is_builtin_sys(ms->cmds->cmd) && (!ms->pp_count))
			check_command(ms);
		ms->cmds = ms->cmds->next;
	}
}

char 		*get_exec_path(t_ms *ms)
{
	int			i;
	char		**tab;
	char		*path;
	struct		stat stats;

	if ((i = get_env(ms->env, "PATH")) != -1)
	{
		tab  = ft_split(ms->env[i] + 5, ':');
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
		ft_error(ms, F_NOT_FOUND_ERR);
	return (NULL);
}

void		check_command_help(t_ms *ms)
{
	char	*path;

	path = NULL;
	if (ms->cmds->cmd[0] == '/' || (ms->cmds->cmd[0] == '.' &&  ms->cmds->cmd[1] == '/') || ft_strchr(ms->cmds->cmd, '/'))
	{
		if (execve(ms->cmds->cmd, ms->cmds->args, ms->env) < 0)
		{
			ft_putstr_fd("minishell: ", 1);
			perror(ms->cmds->cmd);
			exit(1);
		}
	}
	else
	{
		path = get_exec_path(ms);
		(path) ? execve(path, ms->cmds->args, ms->env) : 0;
		(path) ? free(path) : 0;
	}
}

int			check_command(t_ms *ms)
{
	int		ret;

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
		ret = ft_exit(ms);
	else
		check_command_help(ms);
	return (ret);
}
