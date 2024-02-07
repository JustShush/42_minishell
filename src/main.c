/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:34:57 by dimarque          #+#    #+#             */
/*   Updated: 2024/02/07 17:08:16 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_global = 0;

char	**ft_arrdup(t_minishell *ms, char **old)
{
	char	**new;
	int		index;

	index = 0;
	new = malloc(sizeof(char *) * (arr_size(old) + 1));
	if (!new)
		error(ms, 2, NULL);
	while (old && old[index])
	{
		new[index] = ft_strdup(old[index]);
		index++;
	}
	new[index] = NULL;
	return (new);
}

void	minishell(t_minishell *ms)
{
	int		pipe_fd[2];
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
		if (pipe(pipe_fd) < 0)
			pipe_error(ms, pipe_fd);
		pid = fork();
		if (pid < 0)
			fork_error(ms, pipe_fd);
		if (pid == 0)
			child(ms, pipe_fd, cmds_run, pos);
		else
			parent(ms, pipe_fd, cmds_run, pos);
		pos = find_cmd_pos(ms->main_arr, pos);
		cmds_run++;
	}
	get_exit_status(ms, pid, cmds_run);
}
// check_cmd(ms);

t_list	**env_init(char **envp)
{
	int		i;
	char	*buf;
	t_list	*node;
	t_list	**env;

	i = 0;
	env = (t_list **)malloc(sizeof(env));
	*env = NULL;
	while (envp[i])
	{
		buf = ft_strdup(envp[i]);
		node = ft_lstnew(buf);
		node->n = 1;
		ft_lstadd_back(env, node);
		i++;
	}
	free(buf);
	return (env);
}

void	free_main(t_minishell *ms, int argc, char *argv[])
{
	post_process_signal();
	signal_d(ms);
	free(ms->prompt);
	free(ms->input);
	free_arr(ms->main_arr);
	/* if (ms->fdin != -1)
		close(ms->fdin);
	if (ms->fdout != -1)
		close(ms->fdout); */
	(void)argc;
	(void)argv;
}

char	*set_prompt(t_minishell *ms)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*dir;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		prompt = malloc(sizeof(char) * 12);
		if (!prompt)
			error(ms, 2, NULL);
		prompt = "Minishell$> ";
		return (prompt);
	}
	// maybe try to print the entire path until the user (~/documents/42_minishell) instead of (/home/dimarque/documents/42_minishell)
	dir = ft_strjoin(ft_strrchr(getcwd(cwd, sizeof(cwd)), '/') + 1, "$> ");
	if (!dir)
		error(ms, 2, NULL);
	prompt = ft_strjoin("Minishell:", dir);
	if (!prompt)
		error(ms, 2, NULL);
	free(dir);
	return (prompt);
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	if (!ms)
		error(NULL, 2, NULL);
	ms->env = env_init(env);
	ms->exit = 0;
	while (1)
	{
		signal_init();
		ms->prompt = set_prompt(ms);
		ms->input = readline(ms->prompt);
		signal_d(ms);
		if (ft_strlen(ms->input) != 0)
			add_history(ms->input);
		if (ms->input && syntax_error(ms))
			continue;
		if (!var_init(ms))
		{
			minishell(ms);
			free_cmd_list(ms->cmdlist);
		}
		free_main(ms, argc, argv);
	}
	exit(ms->exit);
}

// add single and double quotes to parser
// fix parser error ex: ./minishell ls|echo s < a<b
// output: ls | echo s < a<b
// should be: ls | echo s < a < b

// Add color and symbols to the prompt
// ideas for the prompt:
// \033[1;36mMinishell\033[0m \033[1;33m✗\033[0m
// \033[1;33mMinishell\03[0m$>