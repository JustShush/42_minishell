/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:34:57 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/24 13:53:17 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//int	g_global = 0;

void	minishell(t_minishell *ms)
{
	ms->main_arr = ms_split(ms, ms->input);
	env_var(ms);
	if (!ms->main_arr)
		return ;
	check_cmd(ms);
}

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
		ft_lstadd_back(env, node);
		i++;
	}
	return (env);
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell *ms;

	ms = malloc(sizeof(t_minishell));
	(void)argc;
	(void)argv;
	//(void)env;
	//print_env(env);
	signal_init();
	ms->env = env_init(env);
	while (1)
	{
		ms->prompt = ft_strdup("minishell$> ");
		ms->input = readline(ms->prompt);
		if (ft_strlen(ms->input) != 0)
			add_history(ms->input);
		signal_D(ms);
		var_init(ms);
		minishell(ms);
		free_arr(ms->main_arr);
		free(ms->prompt);
		free(ms->input);
	}
	//minishell(env);
	return (0);
}

// add single and double quotes to parser
// fix parser error ex: ./minishell ls|echo s < a<b
// output: ls | echo s < a<b
// should be: ls | echo s < a < b

// Add color and symbols to the prompt
// My idea is to use ioctl to get the rows of the terminal and when the user types past it the program puts the users cursor one line down using \x1b (https://notes.burke.libbey.me/ansi-escape-codes/)
// GPT https://chat.openai.com/c/3d9eb561-86d7-4b9e-8ac7-79eadb9c015c
// ideas for the prompt:
// \033[1;36mMinishell\033[0m \033[1;33m✗\033[0m
// \033[1;33mMinishell\033[0m$>

/**
 ** Easy Fix!
 * Before parsing everything create a new array that subs all vars for the actual value of the var (replacer)
 * 
 * Create a diff arr just for the commands and flags of those commands
*/