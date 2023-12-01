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

//-n     do not output the trailing newline
int	check_option(char *opt)
{
	if (ft_strncmp(opt, "-n", 2) == 0)
		return (1);
	return (0);
}

void	echo(char **cmd_line)
{
	int	i;

	if (!cmd_line[1])
		return ;
	if (check_option(cmd_line[1]) == 1)
	{
		i = 2;
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