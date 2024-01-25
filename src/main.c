/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:34:57 by dimarque          #+#    #+#             */
/*   Updated: 2024/01/25 14:39:06 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_global = 0;

char **ft_arrdup(t_minishell *ms, char **old)
{
	char **new;
	int index;

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

void minishell(t_minishell *ms)
{
	int pipe_fd[2];
	int cmds_run;
	int pos;
	pid_t pid;

	cmds_run = 0;
	pos = 0;
	if (!ms->cmdlist)
		return;
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

t_list **env_init(char **envp)
{
	int i;
	char *buf;
	t_list *node;
	t_list **env;

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
	return (env);
}

void free_main(t_minishell *ms, int argc, char *argv[])
{
	post_process_signal();
	signal_d(ms);
	free_arr(ms->main_arr);
	free(ms->prompt);
	free(ms->input);
	(void)argc;
	(void)argv;
}

int main(int argc, char *argv[], char **env)
{

	(void)argc;
	(void)argv;
	t_minishell *ms;
	ms = malloc(sizeof(t_minishell));
	if (!ms)
		error(NULL, 2, NULL);
	ms->env = env_init(env);
	while (1)
	{
		signal_init();
		ms->prompt = ft_strdup("Minishell$> ");
		ms->input = readline(ms->prompt);
		printf("input: %s\n", ms->input);
		if (ft_strlen(ms->input) != 0)
			add_history(ms->input);
		if (!var_init(ms))
		{
			minishell(ms);
			free_cmd_list(ms->cmdlist);
		}
		free_main(ms, argc, argv);
	}
}

/*
int	main(int argc, char *argv[], char **env)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	if (!ms)
		error(NULL, 2, NULL);
	ms->env = env_init(env);
	signal_init();
	while (1)
	{
		signal_init();
		ms->prompt = ft_strdup("Minishell$> ");
		printf("input: %s\n", ms->input);
		ms->input = readline(ms->prompt);
		printf("input: %s\n", ms->input);
		if (ft_strlen(ms->input) != 0)
			add_history(ms->input);
		signal_d(ms);
		if (!var_init(ms))
		{
			minishell(ms);
			free_cmd_list(ms->cmdlist);
		}
		free_main(ms, argc, argv);
	}
	return (0);
}
*/
// add single and double quotes to parser
// fix parser error ex: ./minishell ls|echo s < a<b
// output: ls | echo s < a<b
// should be: ls | echo s < a < b

// Add color and symbols to the prompt
// My idea is to use ioctl to get the rows of the terminal and when the user types past it the program puts the users cursor one line down using \x1b (https://notes.burke.libbey.me/ansi-escape-codes/)
// GPT https://chat.openai.com/c/3d9eb561-86d7-4b9e-8ac7-79eadb9c015c
// ideas for the prompt:
// \033[1;36mMinishell\033[0m \033[1;33m✗\033[0m
// \033[1;33mMinishell\03[0m$>

/**
 ** after any command the program exists by it self
 */