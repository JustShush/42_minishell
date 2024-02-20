/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:09:05 by dimarque          #+#    #+#             */
/*   Updated: 2024/01/24 13:09:05 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Creates cmdlist. Initializes cmd_arr
//Similar to ft_lstnew.
t_cmdlist	*cmdlist_lstnew(t_minishell *ms, int cmd_index)
{
	t_cmdlist	*cmdlist;

	cmdlist = malloc(sizeof(t_cmdlist));
	if (!cmdlist)
		error(ms, 2, NULL, NULL);
	cmdlist->cmds = cmd_with_flags(ms, ms->main_arr, cmd_index);
	cmdlist->next = NULL;
	return (cmdlist);
}

t_cmdlist	*cmd_list_init(t_minishell *ms)
{
	int			cmd_n;
	int			i;
	t_cmdlist	*node;
	t_cmdlist	*cmdlist;

	i = 0;
	cmd_n = 0;
	if (ms->cmd_count <= 0)
		return (NULL);
	cmdlist = NULL;
	while (cmd_n < ms->cmd_count)
	{
		node = cmdlist_lstnew(ms, i);
		while (ms->main_arr[i] && ft_strcmp(ms->main_arr[i], "|") != 0)
			i++;
		if (ms->main_arr[i] && ft_strcmp(ms->main_arr[i], "|") == 0)
			i++;
		cmdlist_add_back(&cmdlist, node);
		cmd_n++;
	}
	free_cmd_list(node);
	return (cmdlist);
}

int	var_init(t_minishell *ms)
{
	char	**new_arr;

	ms->cmd_fd = 0;
	ms->fdin = dup(STDIN_FILENO);
	ms->fdout = dup(STDOUT_FILENO);
	ms->main_arr = ms_split(ms, ms->input);
	if (!(ms->main_arr))
		return (1);
	new_arr = replaced_arr(ms);
	free_arr(ms->main_arr);
	ms->main_arr = ft_arrdup(ms, new_arr);
	free_arr(new_arr);
	ms->cmd_count = cmd_count(ms->main_arr);
	ms->cmdlist = cmd_list_init(ms);
	return (0);
}
