/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:04:11 by dimarque          #+#    #+#             */
/*   Updated: 2024/02/06 17:03:52 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
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

void	free_cmd_list(t_cmdlist *cmdlist)
{
	t_cmdlist	*tmp;
	t_cmdlist	*head;

	head = cmdlist;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmds);
		free(tmp);
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr || arr[i])
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

void	free_ms(t_minishell *ms)
{
	int	e;

	if (!ms->exit)
		exit(ms->exit);
	close(0);
	close(1);
	close(2);
	if (ms->fdin != -1)
		close(ms->fdin);
	if (ms->fdout != -1)
		close(ms->fdout);
	if (ms->prompt)
		free(ms->prompt);
	if (ms->input)
		free(ms->input);
	if (ms->main_arr)
		free_arr(ms->main_arr);
	if (ms->cmdlist)
		free_cmd_list(ms->cmdlist);
	free_list(ms->env);
	e = ms->exit;
	free(ms);
	rl_clear_history();
	exit(e);
}
