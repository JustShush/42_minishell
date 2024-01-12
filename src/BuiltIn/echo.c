/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:19 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 10:46:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * The function "echo" prints the command line arguments, with an optional flag to suppress the newline
 * character.
 * 
 * @param opt A string representing an option passed to the function.
 * 
 * @return The function `check_option` returns an integer value. If the `opt` string starts with "-n",
 * it returns 1. Otherwise, it returns 0.
 */
int	check_option(char *opt)
{
	if (ft_strncmp(opt, "-n", 2) == 0)
		return (1);
	return (0);
}

void	command_echo(char **cmd_line, int flag, int i)
{
	if (flag)
	{
		while (cmd_line[i])
		{
			ft_printf("%s", cmd_line[i]);
			if (cmd_line[i + 1] != NULL)
				ft_printf(" ");
			i++;
		}
	}
	else
	{
		i = 1;
		while (cmd_line[i])
		{
			ft_printf("%s ", cmd_line[i]);
			i++;
		}
		ft_printf("\n");
	}
}

void	echo(char **cmd_line)
{
	int	i;
	int	flag;

	if (!cmd_line[1])
		return ;
	flag = 0;
	i = 1;
	while (check_option(cmd_line[i]) == 1)
	{
		flag = 1;
		i++;
	}
	command_echo(cmd_line, flag, i);
}
