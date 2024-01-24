/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:16:14 by dimarque          #+#    #+#             */
/*   Updated: 2023/12/01 17:16:14 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_cmd_pos(char **main_arr, int pos)
{
	while (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") \
		!= 0)
		pos++;
	if (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") == 0)
		pos++;
	return (pos);
}

void	get_exit_status(t_minishell *ms, pid_t pid, int cmds_run)
{
	int	status;

	if (ms->cmd_count == 1 && IsBuiltIn(ms->cmdlist->cmds[0]) \
		== 1)
	{
		wait(&status);
		reset_fds(ms);
		return ;
	}
	while (cmds_run > 0)
	{
		wait(&status);
		if (pid != -1 && WIFEXITED(status))
			ms->exit = WEXITSTATUS(status);
		if (pid != -1 && WIFSIGNALED(status))
			g_global = WTERMSIG(status);
		else
			g_global = 0;
		cmds_run--;
	}
	reset_fds(ms);
}

void	child(t_minishell *ms, int *pipe_fd, int cmds_run, int pos)
{
	t_cmdlist	*cmd;
	int			i;

	cmd = ms->cmdlist;
	i = cmds_run;
	signal(SIGPIPE, signal_process_interrupt);
	while (i > 0)
	{
		cmd = cmd->next;
		i--;
	}
	if (cmds_run != 0)
	{
		dup2(ms->cmd_fd, STDIN_FILENO);
		close(ms->cmd_fd);
	}
	if (cmds_run < ms->cmd_count - 1)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (ms->cmd_count == 1 && IsBuiltIn(cmd->cmds[0]))
		free_ms(ms);
	redirect(ms, ms->main_arr, pos, 1);
	exec(ms, cmd->cmds);
}

void	parent(t_minishell *ms, int *pipe_fd, int cmds_run, int pos)
{
	t_cmdlist	*cmd;
	int			i;

	cmd = ms->cmdlist;
	i = cmds_run;
	while (i-- > 0)
		cmd = cmd->next;
	if (ms->cmd_count == 1)
	{
		if (IsBuiltIn(cmd->cmds[0]) && redirect(ms, ms->main_arr, pos, 0) \
			== 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			builtIn(ms, cmd->cmds, 1);
		}
	}
	if (cmds_run > 0)
		close(ms->cmd_fd);
	if (cmds_run < ms->cmd_count - 1)
		ms->cmd_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
	close(pipe_fd[1]);
	signal(SIGINT, signal_process_interrupt);
}

/* void	ms_pipex(t_minishell *ms)
{
	int		fd[2];
	int		cmds_run;
	int		pos;
	pid_t	pid;

	cmds_run = 0;
	pos = 0;
	if (!ms->cmdlist)
		return ;
	signal(SIGQUIT, signal_process_interrupt);
	while (cmds_run < ms->cmd_count)
	{
		if (pipe(fd) < 0)
			error(ms, 4, "pipe Error.");
		pid = fork();
		if (pid < 0)
			error(ms, 5, "Fork Error.");
		if (pid == 0)
			child(ms, fd, cmds_run, pos);
		else
			parent(ms, fd, cmds_run, pos);
		pos = find_cmd_pos(ms->main_arr, pos);
		cmds_run++;
	}
} */
