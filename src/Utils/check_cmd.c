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

int	isbuiltin(char *str)
{
	if (!str)
		return (0);
	if ((ft_strcmp(str, "echo") == 0) || \
	(ft_strcmp(str, "pwd") == 0) || \
	(ft_strcmp(str, "cd") == 0) || \
	(ft_strcmp(str, "env") == 0) || \
	(ft_strcmp(str, "exit") == 0) || \
	(ft_strcmp(str, "unset") == 0) || \
	(ft_strcmp(str, "export") == 0))
		return (1);
	return (0);
}

void	built_in(t_minishell *ms, char **cmd_flags, int parent)
{
	ms->exit = 0;
	(void)parent;
	if (ft_strcmp(cmd_flags[0], "cd") == 0)
		cd(ms, cmd_flags);
	else if (ft_strcmp(cmd_flags[0], "echo") == 0)
		echo(cmd_flags);
	else if (ft_strcmp(cmd_flags[0], "env") == 0)
		env(ms, cmd_flags);
	else if (ft_strcmp(cmd_flags[0], "exit") == 0)
		ft_exit(ms, cmd_flags); // parent
	else if (ft_strcmp(cmd_flags[0], "export") == 0)
		ft_export(ms, cmd_flags);
	else if (ft_strcmp(cmd_flags[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd_flags[0], "unset") == 0)
		unset(ms, cmd_flags);
}

void	check_cmd(t_minishell *ms)
{
	// printf("%s\n", ms->main_arr[0]);
	if (isbuiltin(ms->main_arr[0]))
		built_in(ms, ms->main_arr, 0);
	// check if is built-in
	// if not then use pipex logic to get the cmd
}
