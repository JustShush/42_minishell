/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:25 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 10:46:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// exit: occ: numeric argument required
int	check_if_num(t_minishell *ms, char *arg)
{
	int i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			error_message(ms, "exit: numeric argument required.\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}

// changes exit nbr in a way, that it is in between 0 and 256
int	calc_exit(int n)
{
	if (n >= 0 && n <= 255)
		return (n);
	else if (n > 255)
	{
		while (n > 255)
			n = n - 256;
	}
	else
	{
		while (n < 0)
			n = n + 256;
	}
	return (n);
}

void	ft_exit(t_minishell *ms, char **cmd_line)
{
	int nbr;

	nbr = 0;
	if (cmd_line && arr_size(cmd_line) == 1)
		nbr = 0;
	else if (cmd_line[1] && arr_size(cmd_line) == 2)
	{
		if (check_if_num(ms, cmd_line[1]) == 0)
			nbr = 2;
		else
			nbr = ft_atoi(cmd_line[1]);
	}
	else if (cmd_line[2] && arr_size(cmd_line) > 2)
	{
		error_message(ms, "exit: too many arguments.\n", NULL);
		nbr = 1;
	}
	nbr = calc_exit(nbr);	
	free_ms(ms);
	exit(nbr);
}
