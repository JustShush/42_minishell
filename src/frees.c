/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:04:11 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/24 17:32:40 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_main(t_minishell *ms, int argc, char *argv[])
{
	check_signal();
	signal_D(ms);
	free(ms->prompt);
	free(ms->input);
	free_arr(ms->main_arr);
	(void)argc;
	(void)argv;
}

void	free_ms(t_minishell *ms)
{
	check_signal();
	if (ms->prompt)
		free(ms->prompt);
	if (ms->input)
		free(ms->input);
	free_list(ms->env);
	free(ms);
	exit(0);
}

void	free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_cmd_list(t_cmdlist *cmdlist)
{
	t_cmdlist	*tmp;
	t_cmdlist	*head;

	head = cmdlist;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd_args);
		free(tmp);
	}
}

void	free_list(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->content);
		free(tmp);
	}
	if (list)
		free(list);
}
