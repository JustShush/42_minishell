/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:31:03 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/17 16:31:03 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

int	IsBuiltIn(char *str)
{
	if ((ft_strcmp(str, "echo") == 0) || (ft_strcmp(str, "pwd") == 0)
	|| (ft_strcmp(str, "cd") == 0) || (ft_strcmp(str, "env") == 0)
	|| (ft_strcmp(str, "exit") == 0) || (ft_strcmp(str, "unset") == 0)
	|| (ft_strcmp(str, "export") == 0))
		return (1);
	return (0);
}

void	builtIn(t_minishell *ms, char **cmd_flags)
{
	if (ft_strcmp(cmd_flags[0], "cd") == 0)
		cd(ms, cmd_flags);
	else if (ft_strcmp(cmd_flags[0], "echo") == 0)
		echo();
	else if (ft_strcmp(cmd_flags[0], "env") == 0)
		env(ms);
	else if (ft_strcmp(cmd_flags[0], "exit") == 0)
		ft_exit();
	else if (ft_strcmp(cmd_flags[0], "export") == 0)
		ft_export();
	else if (ft_strcmp(cmd_flags[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd_flags[0], "unset") == 0)
		unset();
}

int	find_cmd_pos(char **main_arr, int pos)
{
	while (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") \
		!= 0)
		pos++;
	if (main_arr[pos] && main_arr[pos][0] && ft_strcmp(main_arr[pos], "|") == 0)
		pos++;
	return (pos);
}

void	check_cmd(t_minishell *ms)
{
	int	cmd_run;
	int	pos;

	if (!ms->cmdlist)
		error(ms, 3, "check_cmd");
	cmdlist_print(ms->cmdlist);
	pos = 0;
	cmd_run = 0;
	while (cmd_run < ms->cmd_count)
	{
		
		pos = find_cmd_pos(ms->main_arr, pos);
		cmd_run++;
	}
	/* if (IsBuiltIn(ms->main_arr[0]))
		builtIn(ms, ms->main_arr); */
	// check if is built-in
	// if not then use pipex logic to get the cmd
}