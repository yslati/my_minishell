/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslati <yslati@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:56:00 by yslati            #+#    #+#             */
/*   Updated: 2020/11/23 13:00:53 by yslati           ###   ########.fr       */
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

/* void			do_command(t_ms *ms)
{
	
} */


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
			if (tb_len(tmp->next->args) > 1 && !tmp->next->start)
			{
				i = 1;
				while (tmp->next->args[i])
					cmd->args =  get_arr(tmp->next->args[i++], cmd->args);
			}
			fd_in = open_file(tmp);
		}
		else if (tmp->redir == READ)
			read_file(tmp);
		tmp = tmp->next;
	}
	dup2(fd_in, 1);
	close(fd_in);
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
		{
			//printf("========> j : %d\n",ms->j);
			if (ms->j != 0)
			{
				if (dup2(ms->fds[ms->j - 2], 0) < 0)
				{
					perror("dup2");
					exit(0);
				}
			}
			if (ms->cmds->next && !ms->cmds->end)
			{
				if (dup2(ms->fds[ms->j + 1], 1) < 0)
				{
					perror("dup2");
					exit(0);
				}
			}
		}
		i = 0;
		while (i < 2 * ms->pp_count)
			close(ms->fds[i++]);
		if (ms->cmds->redir)
		{
			if (ms->cmds->next->cmd)
			{
				puts("redir");
				ft_redir(tmp, ms->cmds);
			}
			else
			{
				puts("err");
				ft_error(ms, STX_ERR);
			}
		}
		if (ms->cmds->cmd[0] == '/' || (ms->cmds->cmd[0] == '.' &&  ms->cmds->cmd[1] == '/'))
		{
			if (execve(ms->cmds->cmd, ms->cmds->args, ms->env) < 0)
			{
				ft_putstr_fd("minishell: ", 1);
				perror(ms->cmds->cmd);
				exit(0);
			}
		}
		else
			execve(get_exec_path(ms), ms->cmds->args, ms->env);
			/* printf("%s\n", strerror(errno)) */;
		exit(0);
	}
	return (pid);
}

void			exec_command(t_ms *ms)
{
	int		st = 0;
	pid_t	pid;
	int		i;
	
	i = 0;
	ms->fds = (int *)malloc((2 * ms->pp_count)*sizeof(int));
	while (i < 2 * ms->pp_count && ms->pp_count)
	{
		pipe(ms->fds + i * 2);
		i++;
	}
	ms->j = 0;
	while (ms->cmds)
	{
		//puts("oo");

		if ((ms->cmds->next && !ms->cmds->end) || (!is_builtin_sys(ms->cmds->cmd)))
		{
			save_fds(ms->backup);
			while(ms->cmds)
			{
				//puts("ok");
				if ((ms->cmds->start == 0 && ms->cmds->prev->redir) || (ms->cmds->start && is_builtin_sys(ms->cmds->cmd) && (!ms->cmds->redir && !ms->pp_count)))
				{
					// if (ms->cmds->args[1])
					// 	print No such file or directory
					break ;
				}
				pid = run_child(ms);
				//puts("ok1");
				// if (ms->cmds->next && ms->cmds->redir && ms->cmds->end)
				// 	break ;
				if (pid < 0)
				{
					perror("Fork error");
					exit(0);
				}
				if (ms->cmds->end)
					break ;
				else
					ms->cmds = ms->cmds->next;
				ms->j += 2;
				//puts("ok11");
			}
			//puts("ok2");
			i = 0;
			while (i < 2 * ms->pp_count && ms->pp_count)
				close(ms->fds[i++]);
			//puts("ok3");
			if (!ms->pp_count)
				waitpid(pid, &st, 0);
			else
			{
				i = -1;
				//puts("ok4");
				while (++i < ms->pp_count + 1)
				{
					wait(&st);
					/* if (ms->cmds->prev->redir && ms->cmds->end)
						break ; */
				}
				//puts("ok44");
			}
			restore_fds(ms->backup);
			//puts("ok5");
		}
		//puts("ok6");
		if (is_builtin_sys(ms->cmds->cmd))
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
		i = 0;
		while (tab[i])
		{
			path = ft_strjoin(tab[i], "/");
			path = ft_strjoin(path, ms->cmds->cmd);
			if ((stat(path, &stats)) == 0)
			{
				if (stats.st_mode & X_OK)
					return (path);
			}
			i++;
		}
		// !ft_strcmp(ms->cmds->cmd, "") for empty cmd 
		ft_error(ms, 4);
	}
	else
		ft_error(ms, 2);
	//free(path);
	return (NULL);
}

void		check_command(t_ms *ms)
{
	
	if (!ft_strcmp(ms->cmds->cmd, "cd"))
		ft_cd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "pwd"))
		ft_pwd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "env"))
		ft_env(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "export"))
		ft_export(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "unset"))
		ft_unset(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "echo"))
		ft_echo(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "exit"))
		ft_exit(ms);
	// else
	// 	execve(get_exec_path(ms), ms->cmds->args, ms->env);
}
