/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:29:08 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 12:29:08 by marvin           ###   ########.fr       */
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

void	builtIn(t_minishell *ms, char **cmd)
{
	//(void)ms;
	if (ft_strcmp(cmd[0], "cd") == 0)
		cd(ms->main_arr[1]);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		echo();
	else if (ft_strcmp(cmd[0], "env") == 0)
		env();
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit();
	else if (ft_strcmp(cmd[0], "export") == 0)
		export();
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd[0], "unset") == 0)
		unset();
}

void	check_cmd(t_minishell *ms)
{
	if (IsBuiltIn(ms->main_arr[0]))
		builtIn(ms, ms->main_arr);
	// check if is built-in
	// if not then use pipex logic to get the cmd
}