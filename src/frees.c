/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:04:11 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/24 16:44:51 by mde-avel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_ms(t_minishell *ms)
{
	if (ms->prompt)
		free(ms->prompt);
	if (ms->input)
		free(ms->input);
	if (ms->main_arr)
		free_arr(ms->main_arr);
	if (ms->env)
		free_list(ms->env);
	free(ms);
	exit(0);
}